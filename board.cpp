#include "board.h"

Board::Board(QWidget *parent) :
    QFrame(parent)
{

}

Board::~Board()
{

}

void Board::setDataManager(DataManager *dm)
{
    dataManager = dm;
    connect(dataManager, SIGNAL(updateBoard()), this, SLOT(updateBoard()));
}

void Board::updateBoard()
{
    this->update();
}

void Board::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    for(auto coord : dataManager->getPieceCoords())
    {
        QRect rect(coord, QSize(STEP, STEP));
        paint.fillRect(rect, QBrush(dataManager->getPieceColor()));
        QRect innerRect(QPoint(coord.x() + (STEP - m_innerSquareSize) / 2,
                               coord.y() + (STEP - m_innerSquareSize) / 2),
                        QSize(m_innerSquareSize, m_innerSquareSize));
        paint.fillRect(innerRect, QBrush(QColor(Qt::darkGray)));
    }

    for(auto [coords, color] : dataManager->getBoardMap())
    {
        if(color != Qt::transparent)
        {
            QPoint point = QPoint(coords.first, coords.second);
            QRect rect(point, QSize(STEP, STEP));
            paint.fillRect(rect, QBrush(color));
            QRect innerRect(QPoint(point.x() + (STEP - m_innerSquareSize) / 2,
                                   point.y() + (STEP - m_innerSquareSize) / 2),
                            QSize(m_innerSquareSize, m_innerSquareSize));
            paint.fillRect(innerRect, QBrush(QColor(Qt::darkGray)));
        }
    }

    QFrame::paintEvent(e);
}
