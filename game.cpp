#include "game.h"

Game::Game(int s, DataManager *dm) :
    speed(s),
    dataManager(dm)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();
    newPiece();
}

Game::~Game()
{
    delete timer;
}

void Game::move(int direction)
{
    if(direction == RIGHT)
    {
        if(currentPiece->getRightPosition() < dataManager->getRightBorder())
            currentPiece->moveRight();
    }
    else if(direction == LEFT)
    {
        if(currentPiece->getLeftPosition() > dataManager->getLeftBorder())
            currentPiece->moveLeft();
    }
    else if(direction == ROTATE)
    {
        if((currentPiece->getRightPosition() != dataManager->getRightBorder()) &&
           (currentPiece->getLeftPosition() != dataManager->getLeftBorder()))
            currentPiece->rotate();
    }
}

void Game::setSpeed(int speed)
{
    timer->setInterval(speed);
}

void Game::resumeGame()
{
    timer->start();
}

void Game::stopGame()
{
    timer->stop();
}

void Game::startGame()
{
    timer->start(speed);
}

void Game::updateGame()
{
    if(currentPiece->getBottomPosition() != dataManager->getBottomBorder())
    {
        currentPiece->moveDown();
        dataManager->setPieceCoords(currentPiece->getPieceCoords());
    }
    else
    {
        delete currentPiece;
        currentPiece = nullptr;
        newPiece();
    }
}

void Game::newPiece()
{
    currentPiece = PieceFactory::getRandomPiece();
    dataManager->setPieceColor(currentPiece->getColor());
}
