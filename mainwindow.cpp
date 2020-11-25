#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameData1 = new DataManager();
    //gameData2 = new DataManager();
    game1 = new Game(NORMAL, gameData1, 3);
    //game2 = new Game(NORMAL, gameData2, 3);
    ui->frame->setDataManager(gameData1);

    connect(ui->actionVerySlow, &QAction::triggered, this, [&](){ emit speedChanged(VERY_SLOW); });
    connect(ui->actionSlow, &QAction::triggered, this, [&](){ emit speedChanged(SLOW); });
    connect(ui->actionNormal, &QAction::triggered, this, [&](){ emit speedChanged(NORMAL); });
    connect(ui->actionFast, &QAction::triggered, this, [&](){ emit speedChanged(FAST); });
    connect(ui->actionVeryFast, &QAction::triggered, this, [&](){ emit speedChanged(VERY_FAST); });
    connect(this, SIGNAL(speedChanged(int)), game1, SLOT(setSpeed(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(speedChanged(int)), game2, SLOT(setSpeed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(stopGame()), game1, SLOT(stopGame()), Qt::QueuedConnection);
    //connect(this, SIGNAL(stopGame()), game2, SLOT(stopGame()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeGame()), game1, SLOT(resumeGame()), Qt::QueuedConnection);
    //connect(this, SIGNAL(resumeGame()), game2, SLOT(resumeGame()), Qt::QueuedConnection);

    startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameData1;
    //delete gameData2;
}

void MainWindow::startGame()
{
    QThread* thread1 = new QThread();
    game1->moveToThread(thread1);
    connect(thread1, SIGNAL(started()), game1, SLOT(startGame()));
    connect(thread1, SIGNAL(finished()), game1, SLOT(deleteLater()));
    connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));
    thread1->start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(event->Close)
        QApplication::quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    event->accept();

    if(event->key() == Qt::Key_P)
        emit stopGame();
    else if(event->key() == Qt::Key_R)
        emit resumeGame();
    else if(event->key() == Qt::Key_D)
        game1->move(Game::RIGHT);
    else if(event->key() == Qt::Key_A)
        game1->move(Game::LEFT);
    else if(event->key() == Qt::Key_S)
        game1->move(Game::ROTATE);
    else if(event->key() == Qt::Key_Space)
        game1->move(Game::DOWN_FAST);
}
