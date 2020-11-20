#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <iostream>
#include <QObject>
#include <QPoint>
#include <QColor>
#include <QPolygon>
#include <QVector>
#include "defines.h"

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
    int getRightPosition();
    int getLeftPosition();
    int getBottomPosition();
protected:
    std::vector<QPoint> m_pieceCoords;
    QColor m_color{};
    int m_nRot = 0;
    int rightPos = 0;
    int leftPos = 0;
    QPoint startPoint;
};

#endif // TETRISPIECE_H
