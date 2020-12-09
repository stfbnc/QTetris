#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDarkTheme();
    setWindowTitle("Mattoncini");

    running = false;
    isFirstGame = true;
    nGames = DEFAULT_GAMES;

    initializeGame();

    connect(ui->actionVerySlow, &QAction::triggered, this, [&](){ emit speedChanged(VERY_SLOW); });
    connect(ui->actionSlow, &QAction::triggered, this, [&](){ emit speedChanged(SLOW); });
    connect(ui->actionNormal, &QAction::triggered, this, [&](){ emit speedChanged(NORMAL); });
    connect(ui->actionFast, &QAction::triggered, this, [&](){ emit speedChanged(FAST); });
    connect(ui->actionVeryFast, &QAction::triggered, this, [&](){ emit speedChanged(VERY_FAST); });

    connect(ui->actionControls, SIGNAL(triggered()), this, SLOT(openControls()));
    connect(ui->actionGames, SIGNAL(triggered()), this, SLOT(setGames()));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pauseGame()));
}

MainWindow::~MainWindow()
{
    delete ui;

    if(gameData1 != nullptr)
        delete gameData1;
    if(gameData2 != nullptr)
        delete gameData2;

    if(running)
    {
        game1->deleteLater();
        game2->deleteLater();

        thread1->deleteLater();
        thread2->deleteLater();
    }
}

void MainWindow::openControls()
{
    GameControls *ctrlWin = new GameControls(right1, left1, down1, rotate1,
                                             right2, left2, down2, rotate2);
    ctrlWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(ctrlWin, SIGNAL(okPressed(QKeySequence, QKeySequence, QKeySequence, QKeySequence,
                                      QKeySequence, QKeySequence, QKeySequence, QKeySequence)),
            this, SLOT(setControls(QKeySequence, QKeySequence, QKeySequence, QKeySequence,
                                   QKeySequence, QKeySequence, QKeySequence, QKeySequence)));
    ctrlWin->show();
}

void MainWindow::setControls(QKeySequence r1, QKeySequence l1, QKeySequence d1, QKeySequence rot1,
                             QKeySequence r2, QKeySequence l2, QKeySequence d2, QKeySequence rot2)
{
    right1 = r1;
    left1 = l1;
    down1 = d1;
    rotate1 = rot1;
    right2 = r2;
    left2 = l2;
    down2 = d2;
    rotate2 = rot2;
}

void MainWindow::setGames()
{
    bool ok;
    int g = QInputDialog::getInt(this, "Set games", "Games:", nGames, 1, MAX_GAMES, 1, &ok);
    if(ok)
    {
        nGames = g;
        if((game1 != nullptr) && (game2 != nullptr))
        {
            game1->setGames(nGames);
            game2->setGames(nGames);
        }
    }
}

void MainWindow::startGame()
{
    ui->actionGames->setEnabled(false);
    ui->actionControls->setEnabled(false);

    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);

    if(running)
    {
        emit resumeGame();
    }
    else
    {
        running = true;

        if(isFirstGame)
        {
            thread1->start();
            thread2->start();
        }
        else
        {
            setStartingPoints();
            gameData1->initializeMap();
            gameData1->resetScores();
            gameData2->initializeMap();
            gameData2->resetScores();
            emit playAgain();
        }
    }
}

void MainWindow::pauseGame()
{
    ui->actionGames->setEnabled(false);
    ui->actionControls->setEnabled(true);

    ui->startButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);

    emit stopGame();
}

void MainWindow::resetGame()
{
    running = false;
    isFirstGame = false;

    ui->actionGames->setEnabled(true);
    ui->actionControls->setEnabled(true);

    ui->startButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
}

void MainWindow::setDarkTheme()
{
    QPalette darkPalette = QPalette();
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::Button, QColor(123, 123, 123));
    darkPalette.setColor(QPalette::Disabled, QPalette::Light, QColor(123, 123, 123, 0));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(123, 123, 123));

    qApp->setPalette(darkPalette);
    qApp->setStyle("Fusion");
}

void MainWindow::createConnections()
{
    connect(this, SIGNAL(speedChanged(int)), game1, SLOT(setSpeed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(speedChanged(int)), game2, SLOT(setSpeed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(stopGame()), game1, SLOT(stopGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(stopGame()), game2, SLOT(stopGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeGame()), game1, SLOT(resumeGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeGame()), game2, SLOT(resumeGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(playAgain()), game1, SLOT(playAgain()), Qt::QueuedConnection);
    connect(this, SIGNAL(playAgain()), game2, SLOT(playAgain()), Qt::QueuedConnection);
    connect(game1, SIGNAL(endGame()), game2, SLOT(stopGame()));
    connect(game1, SIGNAL(endGame()), this, SLOT(resetGame()));
    connect(game2, SIGNAL(endGame()), game1, SLOT(stopGame()));
    connect(game2, SIGNAL(endGame()), this, SLOT(resetGame()));
    connect(gameData1, SIGNAL(swapLines(std::map<std::pair<int, int>, QColor>, int)),
            gameData2, SLOT(addSwapLines(std::map<std::pair<int, int>, QColor>, int)));
    connect(gameData2, SIGNAL(swapLines(std::map<std::pair<int, int>, QColor>, int)),
            gameData1, SLOT(addSwapLines(std::map<std::pair<int, int>, QColor>, int)));
    connect(gameData1, &DataManager::gameCount, this, [&](int count){
        ui->game_count_1->setText(QString::number(count));
    });
    connect(gameData2, &DataManager::gameCount, this, [&](int count){
        ui->game_count_2->setText(QString::number(count));
    });
    connect(gameData1, &DataManager::updatePoints, this, [&](int p, int l, int s){
        ui->player_1_points->setText(QString::number(p));
        ui->player_1_lines->setText(QString::number(l));
        ui->player_1_swap->setText(QString::number(s));
    });
    connect(gameData2, &DataManager::updatePoints, this, [&](int p, int l, int s){
        ui->player_2_points->setText(QString::number(p));
        ui->player_2_lines->setText(QString::number(l));
        ui->player_2_swap->setText(QString::number(s));
    });

    connect(thread1, SIGNAL(started()), game1, SLOT(startGame()));
    connect(thread1, SIGNAL(finished()), game1, SLOT(deleteLater()));
    connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));

    connect(thread2, SIGNAL(started()), game2, SLOT(startGame()));
    connect(thread2, SIGNAL(finished()), game2, SLOT(deleteLater()));
    connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));
}

void MainWindow::initializeGame()
{
    gameData1 = new DataManager();
    gameData2 = new DataManager();
    game1 = new Game(NORMAL, gameData1, nGames);
    game2 = new Game(NORMAL, gameData2, nGames);
    ui->frame->setDataManager(gameData1);
    ui->frame_2->setDataManager(gameData2);

    thread1 = new QThread();
    thread2 = new QThread();

    game1->moveToThread(thread1);
    game2->moveToThread(thread2);

    createConnections();
    setStartingPoints();
}

void MainWindow::setStartingPoints()
{
    ui->game_count_1->setText("1");
    ui->game_count_2->setText("1");
    ui->player_1_points->setText("0");
    ui->player_1_lines->setText("0");
    ui->player_1_swap->setText("0");
    ui->player_2_points->setText("0");
    ui->player_2_lines->setText("0");
    ui->player_2_swap->setText("0");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(event->Close)
        QApplication::quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(running)
    {
        if(!event->isAutoRepeat())
        {
            event->accept();

            if(event->key() == right1[0])
                game1->move(Game::RIGHT);
            else if(event->key() == left1[0])
                game1->move(Game::LEFT);
            else if(event->key() == rotate1[0])
                game1->move(Game::ROTATE);
            else if(event->key() == down1[0])
                game1->move(Game::DOWN_FAST);
            else if(event->key() == right2[0])
                game2->move(Game::RIGHT);
            else if(event->key() == left2[0])
                game2->move(Game::LEFT);
            else if(event->key() == rotate2[0])
                game2->move(Game::ROTATE);
            else if(event->key() == down2[0])
                game2->move(Game::DOWN_FAST);
        }
    }
}
