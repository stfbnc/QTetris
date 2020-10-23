#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QObject *parent) :
    QObject(parent)
{
    pieceCoords = std::vector<QPoint>();
    createObject();
}

TetrisPiece::~TetrisPiece(){}

void TetrisPiece::createObject()
{
    pieceCoords.push_back(QPoint(10, 10));
}

void TetrisPiece::moveRight()
{
    for(QPoint &p : pieceCoords)
        p += QPoint(step, 0);
}

void TetrisPiece::moveLeft()
{
    for(QPoint &p : pieceCoords)
        p -= QPoint(step, 0);
}

void TetrisPiece::moveDown()
{
    for(QPoint &p : pieceCoords)
        p += QPoint(0, step);
}

void TetrisPiece::rotate()
{

}

std::vector<QPoint> TetrisPiece::getPieceCoords()
{
    return pieceCoords;
}
