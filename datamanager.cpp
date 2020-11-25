#include "datamanager.h"

DataManager::DataManager()
{
    setBorders(0, MAXW, MAXH);
    initializeMap();
}

DataManager::~DataManager()
{

}

void DataManager::setPieceColor(QColor c)
{
    color = c;
}

const QColor DataManager::getPieceColor()
{
    return color;
}

void DataManager::setPieceCoords(std::vector<QPoint> coords)
{
    pieceCoords = coords;
    emit updateBoard();
}

void DataManager::addPieceToBoard()
{
    for(QPoint p : pieceCoords)
    {
        if(p.y() >= 0)
            boardMap[std::pair<int, int>(p.x(), p.y())] = color;
    }
    for(int i = 0; i < MAXH; i += STEP)
    {
        bool lineFull = true;
        for(int j = 0; j < MAXW; j += STEP)
        {
            if(boardMap[std::pair<int, int>(j, i)] == Qt::transparent)
            {
                lineFull = false;
                break;
            }
        }
        if(lineFull)
            removeLine(i);
    }
}

const std::vector<QPoint> DataManager::getPieceCoords()
{
    return pieceCoords;
}

void DataManager::setBorders(int left, int right, int bottom)
{
    leftBorder = left;
    rightBorder = right;
    bottomBorder = bottom;
}

int DataManager::getRightBorder()
{
    return rightBorder;
}

int DataManager::getLeftBorder()
{
    return leftBorder;
}

int DataManager::getBottomBorder()
{
    return bottomBorder;
}

void DataManager::initializeMap()
{
    for(int i = 0; i < MAXW; i += STEP)
    {
        for(int j = 0; j < MAXH; j += STEP)
        {
            boardMap[std::pair<int, int>(i, j)] = Qt::transparent;
        }
    }
}

const std::map<std::pair<int, int>, QColor> DataManager::getBoardMap()
{
    return boardMap;
}

void DataManager::removeLine(int line)
{
    for(int j = 0; j < MAXW; j += STEP)
    {
        for(int i = line; i >= STEP; i -= STEP)
            boardMap[std::pair<int, int>(j, i)] = boardMap[std::pair<int, int>(j, i - STEP)];
        boardMap[std::pair<int, int>(j, 0)] = Qt::transparent;
    }
}
