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

void Game::move(MOVES direction)
{
    if(direction == RIGHT)
    {
        if(currentPiece->getRightPosition() < dataManager->getRightBorder())
        {
            currentPiece->moveRight();
            dataManager->setPieceCoords(currentPiece->getPieceCoords());
        }
    }
    else if(direction == LEFT)
    {
        if(currentPiece->getLeftPosition() > dataManager->getLeftBorder())
        {
            currentPiece->moveLeft();
            dataManager->setPieceCoords(currentPiece->getPieceCoords());
        }
    }
    else if(direction == ROTATE)
    {
        if((currentPiece->getRightPosition() != dataManager->getRightBorder()) &&
           (currentPiece->getLeftPosition() != dataManager->getLeftBorder()))
        {
            currentPiece->rotate();
            dataManager->setPieceCoords(currentPiece->getPieceCoords());
        }
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
    if(canMove(DOWN))
    {
        currentPiece->moveDown();
        dataManager->setPieceCoords(currentPiece->getPieceCoords());
    }
    else
    {
        delete currentPiece;
        currentPiece = nullptr;
        newPiece();
        dataManager->setPieceCoords(currentPiece->getPieceCoords(), true);
    }
}

void Game::newPiece()
{
    currentPiece = PieceFactory::getRandomPiece();
    dataManager->setPieceColor(currentPiece->getColor());
}

bool Game::canMove(MOVES direction)
{
    auto temporaryUpdatedPiece(currentPiece);
    std::map<std::pair<int, int>, QColor> map = dataManager->getBoardMap();
    switch(direction)
    {
        case DOWN:
            temporaryUpdatedPiece->moveDown();
            if(temporaryUpdatedPiece->getBottomPosition() >= dataManager->getBottomBorder())
                return false;
            for(QPoint p : temporaryUpdatedPiece->getPieceCoords())
            {
                if((std::find(currentPiece->getPieceCoords().begin(), currentPiece->getPieceCoords().end(), p) == currentPiece->getPieceCoords().end()) &&
                   (map[std::pair<int, int>(p.x(), p.y())] != Qt::transparent))
                    return false;
            }
            return true;
        case RIGHT:
            return false;
        case LEFT:
            return false;
        case DOWN_FAST:
            return false;
        case ROTATE:
            return false;
    }
}
