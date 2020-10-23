#include "board.h"

Board::Board(QWidget *parent) :
    QFrame(parent)
{}

Board::~Board(){}

void Board::updateBoard(const std::vector<QPoint> &coords)
{
    coordsToFill = coords;
    this->update();
}

void Board::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    for(QPoint c : coordsToFill)
    {
        QRect rect(c, QSize(squareSize, squareSize));
        paint.fillRect(rect, QBrush(QColor(Qt::red)));
        QRect innerRect(QPoint(c.x() + (squareSize - innerSquareSize) / 2, c.y() + (squareSize - innerSquareSize) / 2),
                        QSize(innerSquareSize, innerSquareSize));
        paint.fillRect(innerRect, QBrush(QColor(Qt::darkGray)));
    }

    QFrame::paintEvent(e);
}
