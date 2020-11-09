#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));

    connect(ui->actionVerySlow, &QAction::triggered, this, [&](){ timer->setInterval(VERY_SLOW); });
    connect(ui->actionSlow, &QAction::triggered, this, [&](){ timer->setInterval(SLOW); });
    connect(ui->actionNormal, &QAction::triggered, this, [&](){ timer->setInterval(NORMAL); });
    connect(ui->actionFast, &QAction::triggered, this, [&](){ timer->setInterval(FAST); });
    connect(ui->actionVeryFast, &QAction::triggered, this, [&](){ timer->setInterval(VERY_FAST); });

    startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();
    currentPiece = PieceFactory::getRandomPiece();
    timer->start(VERY_SLOW);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    event->accept();

    if(event->key() == Qt::Key_P)
        timer->stop();
    else if(event->key() == Qt::Key_R)
        timer->start();
    else if(event->key() == Qt::Key_D)
        currentPiece->moveRight();
    else if(event->key() == Qt::Key_A)
        currentPiece->moveLeft();
    else if(event->key() == Qt::Key_S)
        currentPiece->rotate();
}

void MainWindow::updateGame()
{
    ui->frame->updateBoard(currentPiece->getPieceCoords(), currentPiece->getColor());
    currentPiece->moveDown();
}
