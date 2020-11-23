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

void DataManager::setPieceCoords(std::vector<QPoint> coords, bool isNew)
{
    if(!isNew)
    {
        for(QPoint p : pieceCoords)
            boardMap[std::pair<int, int>(p.x(), p.y())] = Qt::transparent;
    }
    for(QPoint p : coords)
        boardMap[std::pair<int, int>(p.x(), p.y())] = color;
    pieceCoords = coords;

    emit updateBoard();
}

/*std::vector<QPoint> DataManager::getPieceCoords()
{
    return pieceCoords;
}*/

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
    for(int i = 0; i < (MAXH / STEP); ++i)
    {
        for(int j = 0; j < (MAXW / STEP); ++j)
        {
            boardMap[std::pair<int, int>(i, j)] = Qt::transparent;
        }
    }
}

const std::map<std::pair<int, int>, QColor> DataManager::getBoardMap()
{
    return boardMap;
}
