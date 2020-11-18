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
    dataManager->setBorders(0, MAXW);
    connect(dataManager, SIGNAL(updateBoard()), this, SLOT(updateBoard()));
}

void Board::updateBoard()
{
    this->update();
}

void Board::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    for(QPoint c : dataManager->getPieceCoords())
    {
        QRect rect(c, QSize(STEP, STEP));
        paint.fillRect(rect, QBrush(dataManager->getPieceColor()));
        QRect innerRect(QPoint(c.x() + (STEP - m_innerSquareSize) / 2,
                               c.y() + (STEP - m_innerSquareSize) / 2),
                        QSize(m_innerSquareSize, m_innerSquareSize));
        paint.fillRect(innerRect, QBrush(QColor(Qt::darkGray)));
    }

    QFrame::paintEvent(e);
}
