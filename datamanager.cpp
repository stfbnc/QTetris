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
