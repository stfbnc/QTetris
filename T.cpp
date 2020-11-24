#include <T.h>

T::T() :
    TetrisPiece(QColor(Qt::darkGray))
{
    initialize();
    m_nRot = 0;
}

T::~T(){}

T* T::clone() const
{
    return new T(*this);
}

void T::initialize()
{
    m_pieceCoords.push_back(QPoint(startPoint.x() - STEP, startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
}

void T::rotate()
{
    if(m_nRot == 0)
    {
        m_pieceCoords.at(0) += QPoint(STEP, -STEP);
        m_pieceCoords.at(2) += QPoint(-STEP, STEP);
        m_pieceCoords.at(3) += QPoint(-STEP, -STEP);
        m_nRot = 1;
    }
    else if(m_nRot == 1)
    {
        m_pieceCoords.at(0) += QPoint(STEP, STEP);
        m_pieceCoords.at(2) += QPoint(-STEP, -STEP);
        m_pieceCoords.at(3) += QPoint(STEP, -STEP);
        m_nRot = 2;
    }
    else if(m_nRot == 2)
    {
        m_pieceCoords.at(0) += QPoint(-STEP, STEP);
        m_pieceCoords.at(2) += QPoint(STEP, -STEP);
        m_pieceCoords.at(3) += QPoint(STEP, STEP);
        m_nRot = 3;
    }
    else if(m_nRot == 3)
    {
        m_pieceCoords.at(0) += QPoint(-STEP, -STEP);
        m_pieceCoords.at(2) += QPoint(STEP, STEP);
        m_pieceCoords.at(3) += QPoint(-STEP, STEP);
        m_nRot = 0;
    }
}
