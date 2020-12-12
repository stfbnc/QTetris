#include "game.h"

Game::Game(int s, DataManager *dm, int nGames) :
    maxGames(nGames),
    speed(s),
    dataManager(dm)
{
    gameCount = 1;
    running = false;
    moving = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();
}

Game::~Game()
{
    delete timer;

    if(currentPiece != nullptr)
        delete currentPiece;
}

void Game::move(MOVES direction)
{
    moving = true;
    if(running)
    {
        if(canMove(direction))
        {
            switch(direction)
            {
                case RIGHT:
                    currentPiece->moveRight();
                    dataManager->setPieceCoords(currentPiece->getPieceCoords());
                    break;
                case LEFT:
                    currentPiece->moveLeft();
                    dataManager->setPieceCoords(currentPiece->getPieceCoords());
                    break;
                case ROTATE:
                    currentPiece->rotate();
                    dataManager->setPieceCoords(currentPiece->getPieceCoords());
                    break;
                case DOWN_FAST:
                    running = false;
                    while(canMove(DOWN))
                        currentPiece->moveDown();
                    dataManager->setPieceCoords(currentPiece->getPieceCoords());
                    dataManager->addPoints(PIECE_DROPPED_POINTS);
                    running = true;
                    break;
                case DOWN:
                    break;
            }
        }
    }
    moving = false;
}

void Game::setGames(int games)
{
    maxGames = games;
}

void Game::resetGames()
{
    gameCount = 1;
}

void Game::setSpeed(int speed)
{
    this->speed = speed;
    timer->setInterval(speed);
}

void Game::resumeGame()
{
    running = true;
    timer->start(speed);
}

void Game::playAgain()
{
    running = true;
    newPiece();
    timer->start(speed);
}

void Game::stopGame()
{
    running = false;
    timer->stop();
}

void Game::startGame()
{
    running = true;
    newPiece();
    timer->start(speed);
}

void Game::updateGame()
{
    if(!moving)
    {
        if(canMove(DOWN))
        {
            currentPiece->moveDown();
            dataManager->setPieceCoords(currentPiece->getPieceCoords());
        }
        else
        {
            bool gameLost = true;
            for(QPoint p : currentPiece->getPieceCoords())
            {
                if(p.y() >= 0)
                {
                    gameLost = false;
                    break;
                }
            }

            if(gameLost)
            {
                if(gameCount < maxGames)
                {
                    dataManager->initializeMap();
                    gameCount++;
                    dataManager->increaseGameCount();
                    deletePiece();
                    newPiece();
                }
                else
                {
                    //gameCount = 1;
                    stopGame();
                    deletePiece();
                    emit endGame();
                }
            }
            else
            {
                dataManager->addPoints(PIECE_POINTS);
                dataManager->addPieceToBoard();
                deletePiece();
                newPiece();
            }
        }
    }
}

void Game::newPiece()
{
    currentPiece = PieceFactory::getRandomPiece();
    dataManager->setPieceCoords(currentPiece->getPieceCoords());
    dataManager->setPieceColor(currentPiece->getColor());
}

void Game::deletePiece()
{
    delete currentPiece;
    currentPiece = nullptr;
}

bool Game::canMove(MOVES direction)
{
    auto temporaryUpdatedPiece = currentPiece->clone();
    std::map<std::pair<int, int>, QColor> map = dataManager->getBoardMap();

    switch(direction)
    {
        case DOWN:
            temporaryUpdatedPiece->moveDown();
            if(temporaryUpdatedPiece->getBottomPosition() > dataManager->getBottomBorder())
                return false;
            for(QPoint p : temporaryUpdatedPiece->getPieceCoords())
            {
                if(p.y() >= 0)
                {
                    if(map[std::pair<int, int>(p.x(), p.y())] != Qt::transparent)
                        return false;
                }
            }
            return true;
        case RIGHT:
            temporaryUpdatedPiece->moveRight();
            if(temporaryUpdatedPiece->getRightPosition() > dataManager->getRightBorder())
                return false;
            for(QPoint p : temporaryUpdatedPiece->getPieceCoords())
            {
                if(p.y() >= 0)
                {
                    if(map[std::pair<int, int>(p.x(), p.y())] != Qt::transparent)
                        return false;
                }
            }
            return true;
        case LEFT:
            temporaryUpdatedPiece->moveLeft();
            if(temporaryUpdatedPiece->getLeftPosition() < dataManager->getLeftBorder())
                return false;
            for(QPoint p : temporaryUpdatedPiece->getPieceCoords())
            {
                if(p.y() >= 0)
                {
                    if(map[std::pair<int, int>(p.x(), p.y())] != Qt::transparent)
                        return false;
                }
            }
            return true;
        case DOWN_FAST:
            return true;
        case ROTATE:
            temporaryUpdatedPiece->rotate();
            if(temporaryUpdatedPiece->getLeftPosition() < dataManager->getLeftBorder())
                return false;
            if(temporaryUpdatedPiece->getRightPosition() > dataManager->getRightBorder())
                return false;
            if(temporaryUpdatedPiece->getBottomPosition() > dataManager->getBottomBorder())
                return false;
            for(QPoint p : temporaryUpdatedPiece->getPieceCoords())
            {
                if(p.y() >= 0)
                {
                    if(map[std::pair<int, int>(p.x(), p.y())] != Qt::transparent)
                        return false;
                }
            }
            return true;
    }

    delete temporaryUpdatedPiece;
}
