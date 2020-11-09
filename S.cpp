#include <S.h>

S::S() :
    TetrisPiece(QColor(Qt::magenta))
{
    initialize();
}

S::~S(){}

void S::initialize()
{
    m_pieceCoords.push_back(QPoint(10, 10));
    m_pieceCoords.push_back(QPoint(10, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + m_step));
    m_pieceCoords.push_back(QPoint(10 + m_step, 10 + 2 * m_step));
}

void S::rotate()
{

}
