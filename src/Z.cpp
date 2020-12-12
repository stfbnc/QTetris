#include <Z.h>

Z::Z() :
    TetrisPiece(QColor(Qt::blue))
{
    initialize();
    m_nRot = 0;
}

Z::~Z(){}

Z* Z::clone() const
{
    return new Z(*this);
}

void Z::initialize()
{
    m_pieceCoords.push_back(QPoint(startPoint.x() - STEP, startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y() + STEP));
}

void Z::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(2 * STEP, 0);
        m_pieceCoords.at(1) += QPoint(STEP, STEP);
        m_pieceCoords.at(3) += QPoint(-STEP, STEP);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(-2 * STEP, 0);
        m_pieceCoords.at(1) += QPoint(-STEP, -STEP);
        m_pieceCoords.at(3) += QPoint(STEP, -STEP);
        m_nRot = 0;
    }
}
