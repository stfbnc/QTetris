#include "mainwindow.h"
#include "ui_mainwindow.h"

/* TODO:
 * swap lines
 * set number of games (if running, only > current games and < max games. If not running, < max games. Signal games of the change)
 * end of the game (deleting all objects and setting them to nullptr)
 * strings translation file
 * conditional opening of menus
 * graphics
 */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    running = false;

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
        initializeGame();
        createConnections();

        thread1 = new QThread();
        game1->moveToThread(thread1);
        connect(thread1, SIGNAL(started()), game1, SLOT(startGame()));
        connect(thread1, SIGNAL(finished()), game1, SLOT(deleteLater()));
        connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));

        thread2 = new QThread();
        game2->moveToThread(thread2);
        connect(thread2, SIGNAL(started()), game2, SLOT(startGame()));
        connect(thread2, SIGNAL(finished()), game2, SLOT(deleteLater()));
        connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));

        thread1->start();
        thread2->start();
    }
}

void MainWindow::resetGame()
{
    delete gameData1;
    gameData1 = nullptr;
    delete gameData2;
    gameData2 = nullptr;

    running = false;
}

void MainWindow::createConnections()
{
    connect(this, SIGNAL(speedChanged(int)), game1, SLOT(setSpeed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(speedChanged(int)), game2, SLOT(setSpeed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(stopGame()), game1, SLOT(stopGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(stopGame()), game2, SLOT(stopGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeGame()), game1, SLOT(resumeGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeGame()), game2, SLOT(resumeGame()), Qt::QueuedConnection);
    connect(gameData1, SIGNAL(swapLines(std::map<std::pair<int, int>, QColor>, int)),
            gameData2, SLOT(addSwapLines(std::map<std::pair<int, int>, QColor>, int)));
    connect(gameData2, SIGNAL(swapLines(std::map<std::pair<int, int>, QColor>, int)),
            gameData1, SLOT(addSwapLines(std::map<std::pair<int, int>, QColor>, int)));
}

void MainWindow::initializeGame()
{
    gameData1 = new DataManager();
    gameData2 = new DataManager();
    game1 = new Game(NORMAL, gameData1, 3);
    game2 = new Game(NORMAL, gameData2, 3);
    ui->frame->setDataManager(gameData1);
    ui->frame_2->setDataManager(gameData2);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(event->Close)
        QApplication::quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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
