#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QColor color, QObject *parent) :
    QObject(parent),
    m_color(color)
{
    startPoint = QPoint(((MAXW / STEP) / 2) * STEP, -2 * STEP);
}

TetrisPiece::TetrisPiece(const TetrisPiece &tp)
{
    m_pieceCoords = tp.m_pieceCoords;
    m_nRot = tp.m_nRot;
    m_color = tp.m_color;
    rightPos = tp.rightPos;
    leftPos = tp.leftPos;
    startPoint = tp.startPoint;
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
        p += QPoint(0, STEP);
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
