#include "board.h"

Board::Board(QWidget *parent) :
    QFrame(parent)
{
    dataManager = nullptr;
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

    if(dataManager != nullptr)
    {
        QColor pColor = dataManager->getPieceColor();
        for(auto coord : dataManager->getPieceCoords())
        {
            QRect rect(coord, QSize(STEP, STEP));
            paint.fillRect(rect, QBrush(pColor));

            paint.setPen(pColor.lighter());
            paint.drawLine(coord.x(), coord.y() + STEP - 1, coord.x(), coord.y());
            paint.drawLine(coord.x(), coord.y(), coord.x() + STEP - 1, coord.y());

            paint.setPen(pColor.darker());
            paint.drawLine(coord.x() + 1, coord.y() + STEP - 1,
                           coord.x() + STEP - 1, coord.y() + STEP - 1);
            paint.drawLine(coord.x() + STEP - 1, coord.y() + STEP - 1,
                           coord.x() + STEP - 1, coord.y() + 1);
        }

        for(auto [coords, color] : dataManager->getBoardMap())
        {
            if(color != Qt::transparent)
            {
                QPoint point = QPoint(coords.first, coords.second);
                QRect rect(point, QSize(STEP, STEP));
                paint.fillRect(rect, QBrush(color));

                paint.setPen(color.lighter());
                paint.drawLine(coords.first, coords.second + STEP - 1, coords.first, coords.second);
                paint.drawLine(coords.first, coords.second, coords.first + STEP - 1, coords.second);

                paint.setPen(color.darker());
                paint.drawLine(coords.first + 1, coords.second + STEP - 1,
                               coords.first + STEP - 1, coords.second + STEP - 1);
                paint.drawLine(coords.first + STEP - 1, coords.second + STEP - 1,
                               coords.first + STEP - 1, coords.second + 1);
            }
        }
    }

    QFrame::paintEvent(e);
}
