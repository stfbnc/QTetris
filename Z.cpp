#include <Z.h>

Z::Z() :
    TetrisPiece(QColor(Qt::blue))
{
    initialize();
    m_nRot = 0;
}

Z::~Z(){}

void Z::initialize()
{
    m_pieceCoords.push_back(QPoint(10 - m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
}

void Z::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(2 * m_step, 0);
        m_pieceCoords.at(1) += QPoint(m_step, m_step);
        m_pieceCoords.at(3) += QPoint(-m_step, m_step);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(-2 * m_step, 0);
        m_pieceCoords.at(1) += QPoint(-m_step, -m_step);
        m_pieceCoords.at(3) += QPoint(m_step, -m_step);
        m_nRot = 0;
    }
}
