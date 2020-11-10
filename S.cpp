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
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10));
    m_pieceCoords.push_back(QPoint(10 - m_step, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
}

void S::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(m_step, m_step);
        m_pieceCoords.at(1) += QPoint(0, 2 * m_step);
        m_pieceCoords.at(2) += QPoint(m_step, -m_step);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(-m_step, -m_step);
        m_pieceCoords.at(1) += QPoint(0, -2 * m_step);
        m_pieceCoords.at(2) += QPoint(-m_step, m_step);
        m_nRot = 0;
    }
}
