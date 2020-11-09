#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QColor color, QObject *parent) :
    m_color(color),
    QObject(parent)
{
}

TetrisPiece::~TetrisPiece(){}

void TetrisPiece::moveRight()
{
    for(QPoint &p : m_pieceCoords)
        p += QPoint(m_step, 0);
}

void TetrisPiece::moveLeft()
{
    for(QPoint &p : m_pieceCoords)
        p -= QPoint(m_step, 0);
}

void TetrisPiece::moveDown()
{
    for(QPoint &p : m_pieceCoords)
        p += QPoint(0, m_step);
}

std::vector<QPoint> TetrisPiece::getPieceCoords()
{
    return m_pieceCoords;
}

QColor TetrisPiece::getColor()
{
    return m_color;
}
