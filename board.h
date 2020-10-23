#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include <QPainter>

class Board : public QFrame
{
Q_OBJECT
public:
    explicit Board(QWidget *parent=nullptr);
    virtual ~Board();
    void updateBoard(const std::vector<QPoint> &coords);
private:
    void paintEvent(QPaintEvent *e) override;

    const int squareSize = 20;
    const int innerSquareSize = 8;
    std::vector<QPoint> coordsToFill = std::vector<QPoint>();
};

#endif // BOARD_H
