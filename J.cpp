#include <J.h>

J::J() :
    TetrisPiece(QColor(Qt::yellow))
{
    initialize();
    m_nRot = 0;
}

J::~J(){}

void J::initialize()
{
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + 2 * m_step, 10 + m_step));
}

void J::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(2 * m_step, 0);
        m_pieceCoords.at(1) += QPoint(m_step, -m_step);
        m_pieceCoords.at(3) += QPoint(-m_step, m_step);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(0, m_step);
        m_pieceCoords.at(1) += QPoint(m_step, 0);
        m_pieceCoords.at(2) += QPoint(0, -m_step);
        m_pieceCoords.at(3) += QPoint(-m_step, -2 * m_step);
        m_nRot = 2;
    }
    else if(m_nRot == 2)
    {
        m_pieceCoords.at(0) += QPoint(-2 * m_step, 0);
        m_pieceCoords.at(1) += QPoint(-m_step, m_step);
        m_pieceCoords.at(3) += QPoint(m_step, -m_step);
        m_nRot = 3;
    }
    else if(m_nRot == 3)
    {
        m_pieceCoords.at(0) += QPoint(0, -m_step);
        m_pieceCoords.at(1) += QPoint(-m_step, 0);
        m_pieceCoords.at(2) += QPoint(0, m_step);
        m_pieceCoords.at(3) += QPoint(m_step, 2 * m_step);
        m_nRot = 0;
    }
}
