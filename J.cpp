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
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y() + STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x() + 2 * STEP, startPoint.y() + STEP));
}

void J::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(2 * STEP, 0);
        m_pieceCoords.at(1) += QPoint(STEP, -STEP);
        m_pieceCoords.at(3) += QPoint(-STEP, STEP);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(0, 2 * STEP);
        m_pieceCoords.at(1) += QPoint(STEP, STEP);
        m_pieceCoords.at(3) += QPoint(-STEP, -STEP);
        m_nRot = 2;
    }
    else if(m_nRot == 2)
    {
        m_pieceCoords.at(0) += QPoint(-2 * STEP, 0);
        m_pieceCoords.at(1) += QPoint(-STEP, STEP);
        m_pieceCoords.at(3) += QPoint(STEP, -STEP);
        m_nRot = 3;
    }
    else if(m_nRot == 3)
    {
        m_pieceCoords.at(0) += QPoint(0, -2 * STEP);
        m_pieceCoords.at(1) += QPoint(-STEP, -STEP);
        m_pieceCoords.at(3) += QPoint(STEP, STEP);
        m_nRot = 0;
    }
}
