#include <I.h>

I::I() :
    TetrisPiece(QColor(Qt::darkGreen))
{
    initialize();
    m_nRot = 0;
}

I::~I(){}

I* I::clone() const
{
    return new I(*this);
}

void I::initialize()
{
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() - 2 * STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() - STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
}

void I::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(-STEP, 2 * STEP);
        m_pieceCoords.at(1) += QPoint(0, STEP);
        m_pieceCoords.at(2) += QPoint(STEP, 0);
        m_pieceCoords.at(3) += QPoint(2 * STEP, -STEP);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(STEP, -2 * STEP);
        m_pieceCoords.at(1) += QPoint(0, -STEP);
        m_pieceCoords.at(2) += QPoint(-STEP, 0);
        m_pieceCoords.at(3) += QPoint(-2 * STEP, STEP);
        m_nRot = 0;
    }
}
