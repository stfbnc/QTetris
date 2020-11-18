#include <S.h>

S::S() :
    TetrisPiece(QColor(Qt::magenta))
{
    initialize();
    m_nRot = 0;
}

S::~S(){}

void S::initialize()
{
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x() - STEP, startPoint.y() + STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
}

void S::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(STEP, STEP);
        m_pieceCoords.at(1) += QPoint(0, 2 * STEP);
        m_pieceCoords.at(2) += QPoint(STEP, -STEP);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(-STEP, -STEP);
        m_pieceCoords.at(1) += QPoint(0, -2 * STEP);
        m_pieceCoords.at(2) += QPoint(-STEP, STEP);
        m_nRot = 0;
    }
}
