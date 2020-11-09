#include "board.h"

Board::Board(QWidget *parent) :
    QFrame(parent)
{}

Board::~Board(){}

void Board::updateBoard(const std::vector<QPoint> &coords, const QColor color)
{
    m_coordsToFill = coords;
    m_color = color;
    this->update();
}

void Board::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    for(QPoint c : m_coordsToFill)
    {
        QRect rect(c, QSize(m_squareSize, m_squareSize));
        paint.fillRect(rect, QBrush(m_color));
        QRect innerRect(QPoint(c.x() + (m_squareSize - m_innerSquareSize) / 2,
                               c.y() + (m_squareSize - m_innerSquareSize) / 2),
                        QSize(m_innerSquareSize, m_innerSquareSize));
        paint.fillRect(innerRect, QBrush(QColor(Qt::darkGray)));
    }

    QFrame::paintEvent(e);
}
