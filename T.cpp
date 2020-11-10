#include <T.h>

T::T() :
    TetrisPiece(QColor(Qt::darkGray))
{
    initialize();
    m_nRot = 0;
}

T::~T(){}

void T::initialize()
{
    m_pieceCoords.push_back(QPoint(10 - m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
}

void T::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(m_step, -m_step);
        m_pieceCoords.at(2) += QPoint(-m_step, m_step);
        m_pieceCoords.at(3) += QPoint(-m_step, -m_step);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(m_step, m_step);
        m_pieceCoords.at(2) += QPoint(-m_step, -m_step);
        m_pieceCoords.at(3) += QPoint(m_step, -m_step);
        m_nRot = 2;
    }
    else if(m_nRot == 2)
    {
        m_pieceCoords.at(0) += QPoint(-m_step, m_step);
        m_pieceCoords.at(2) += QPoint(m_step, -m_step);
        m_pieceCoords.at(3) += QPoint(m_step, m_step);
        m_nRot = 3;
    }
    else if(m_nRot == 3)
    {
        m_pieceCoords.at(0) += QPoint(-m_step, -m_step);
        m_pieceCoords.at(2) += QPoint(m_step, m_step);
        m_pieceCoords.at(3) += QPoint(-m_step, m_step);
        m_nRot = 0;
    }
}
