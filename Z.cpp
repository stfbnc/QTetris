#include <Z.h>

Z::Z() :
    TetrisPiece(QColor(Qt::blue))
{
    initialize();
}

Z::~Z(){}

void Z::initialize()
{
    m_pieceCoords.push_back(QPoint(10 + m_step, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10, 10 + 2 * m_step));
}

void Z::rotate()
{

}
