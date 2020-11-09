#include <I.h>

I::I() :
    TetrisPiece(QColor(Qt::darkGreen))
{
    initialize();
    m_nRot = 0;
}

I::~I(){}

void I::initialize()
{
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10, 10 + 2 * m_step));
    m_pieceCoords.push_back(QPoint(10, 10 + 3 * m_step));
}

void I::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(-m_step, 2 * m_step);
        m_pieceCoords.at(1) += QPoint(0, m_step);
        m_pieceCoords.at(2) += QPoint(m_step, 0);
        m_pieceCoords.at(3) += QPoint(2 * m_step, -m_step);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(m_step, -2 * m_step);
        m_pieceCoords.at(1) += QPoint(0, -m_step);
        m_pieceCoords.at(2) += QPoint(-m_step, 0);
        m_pieceCoords.at(3) += QPoint(-2 * m_step, m_step);
        m_nRot = 0;
    }
}
