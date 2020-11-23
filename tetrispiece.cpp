#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QColor color, QObject *parent) :
    m_color(color),
    QObject(parent)
{
    startPoint = QPoint(((MAXW / STEP) / 2) * STEP, 0);
}

TetrisPiece::TetrisPiece(const TetrisPiece &tp)
{
    m_pieceCoords = tp.m_pieceCoords;
}

TetrisPiece::~TetrisPiece(){}

void TetrisPiece::moveRight()
{
    for(QPoint &p : m_pieceCoords)
        p += QPoint(STEP, 0);
}

void TetrisPiece::moveLeft()
{
    for(QPoint &p : m_pieceCoords)
        p -= QPoint(STEP, 0);
}

void TetrisPiece::moveDown()
{
    for(QPoint &p : m_pieceCoords)
        p += QPoint(0, SMALL_STEP);
}

std::vector<QPoint> TetrisPiece::getPieceCoords()
{
    return m_pieceCoords;
}

QColor TetrisPiece::getColor()
{
    return m_color;
}

int TetrisPiece::getRightPosition()
{
    QPolygon poly(QVector<QPoint>(m_pieceCoords.begin(), m_pieceCoords.end()));
    return (poly.boundingRect().right() + STEP);
}

int TetrisPiece::getLeftPosition()
{
    QPolygon poly(QVector<QPoint>(m_pieceCoords.begin(), m_pieceCoords.end()));
    return poly.boundingRect().left();
}

int TetrisPiece::getBottomPosition()
{
    QPolygon poly(QVector<QPoint>(m_pieceCoords.begin(), m_pieceCoords.end()));
    return (poly.boundingRect().bottom() + STEP);
}
