#include "mainwindow.h"
#include "ui_mainwindow.h"

/* TODO:
 * set number of games (if running, only > current games and < max games. If not running, < max games. Signal games of the change)
 * conditional opening of menus
 * graphics
 */


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

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->pauseButton, &QPushButton::clicked, this, [&](){
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        emit stopGame();
    });
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

void MainWindow::startGame()
{
    this->ui->startButton->setEnabled(false);
    this->ui->pauseButton->setEnabled(true);

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

void MainWindow::resetGame()
{
    running = false;
    isFirstGame = false;

    this->ui->startButton->setEnabled(true);
    this->ui->pauseButton->setEnabled(false);
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
        this->ui->game_count_1->setText(QString::number(count));
    });
    connect(gameData2, &DataManager::gameCount, this, [&](int count){
        this->ui->game_count_2->setText(QString::number(count));
    });
    connect(gameData1, &DataManager::updatePoints, this, [&](int p, int l, int s){
        this->ui->player_1_points->setText(QString::number(p));
        this->ui->player_1_lines->setText(QString::number(l));
        this->ui->player_1_swap->setText(QString::number(s));
    });
    connect(gameData2, &DataManager::updatePoints, this, [&](int p, int l, int s){
        this->ui->player_2_points->setText(QString::number(p));
        this->ui->player_2_lines->setText(QString::number(l));
        this->ui->player_2_swap->setText(QString::number(s));
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
    this->ui->game_count_1->setText("1");
    this->ui->game_count_2->setText("1");
    this->ui->player_1_points->setText("0");
    this->ui->player_1_lines->setText("0");
    this->ui->player_1_swap->setText("0");
    this->ui->player_2_points->setText("0");
    this->ui->player_2_lines->setText("0");
    this->ui->player_2_swap->setText("0");
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
        event->accept();

        if(event->key() == Qt::Key_D)
            game1->move(Game::RIGHT);
        else if(event->key() == Qt::Key_A)
            game1->move(Game::LEFT);
        else if(event->key() == Qt::Key_S)
            game1->move(Game::ROTATE);
        else if(event->key() == Qt::Key_X)
            game1->move(Game::DOWN_FAST);
        else if(event->key() == Qt::Key_Right)
            game2->move(Game::RIGHT);
        else if(event->key() == Qt::Key_Left)
            game2->move(Game::LEFT);
        else if(event->key() == Qt::Key_Up)
            game2->move(Game::ROTATE);
        else if(event->key() == Qt::Key_Down)
            game2->move(Game::DOWN_FAST);
    }
}
