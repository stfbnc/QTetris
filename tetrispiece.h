#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QObject>
#include <QPoint>
#include <QColor>

class TetrisPiece : public QObject
{
Q_OBJECT
public:
    explicit TetrisPiece(QColor color, QObject *parent=nullptr);
    virtual ~TetrisPiece();
    virtual void initialize() = 0;
    void moveRight();
    void moveLeft();
    void moveDown();
    virtual void rotate() = 0;
    std::vector<QPoint> getPieceCoords();
    QColor getColor();
protected:
    std::vector<QPoint> m_pieceCoords;
    QColor m_color{};
    int m_nRot = 0;

    const int m_step = 20;
};

#endif // TETRISPIECE_H
