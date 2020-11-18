#include "datamanager.h"

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

void DataManager::setPieceColor(QColor c)
{
    color = c;
}

QColor DataManager::getPieceColor()
{
    return color;
}

void DataManager::setPieceCoords(std::vector<QPoint> coords)
{
    pieceCoords = coords;
    emit updateBoard();
}

std::vector<QPoint> DataManager::getPieceCoords()
{
    return pieceCoords;
}

void DataManager::setBorders(int left, int right)
{
    leftBorder = left;
    rightBorder = right;
}

int DataManager::getRightBorder()
{
    return rightBorder;
}

int DataManager::getLeftBorder()
{
    return leftBorder;
}
