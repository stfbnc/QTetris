#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include <QPainter>
#include <QColor>

class Board : public QFrame
{
Q_OBJECT
public:
    explicit Board(QWidget *parent=nullptr);
    virtual ~Board();
    void updateBoard(const std::vector<QPoint> &coords, const QColor color);
private:
    void paintEvent(QPaintEvent *e) override;

    const int m_squareSize = 20;
    const int m_innerSquareSize = 8;
    std::vector<QPoint> m_coordsToFill = std::vector<QPoint>();
    QColor m_color;
};

#endif // BOARD_H
