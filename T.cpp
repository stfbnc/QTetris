#include <T.h>

T::T() :
    TetrisPiece(QColor(Qt::darkGray))
{
    initialize();
}

T::~T(){}

void T::initialize()
{
    m_pieceCoords.push_back(QPoint(10 + m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + 2 * m_step, 10 + m_step));
}

void T::rotate()
{

}
