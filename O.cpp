#include <O.h>

O::O() :
    TetrisPiece(QColor(Qt::red))
{
    initialize();
    m_nRot = 0;
}

O::~O(){}

void O::initialize()
{
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
}

void O::rotate()
{

}
