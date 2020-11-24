#include <O.h>

O::O() :
    TetrisPiece(QColor(Qt::red))
{
    initialize();
    m_nRot = 0;
}

O::~O(){}

O* O::clone() const
{
    return new O(*this);
}

void O::initialize()
{
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y()));
    m_pieceCoords.push_back(QPoint(startPoint.x(), startPoint.y() + STEP));
    m_pieceCoords.push_back(QPoint(startPoint.x() + STEP, startPoint.y() + STEP));
}

void O::rotate()
{

}
