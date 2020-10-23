#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QObject>
#include <QPoint>

class TetrisPiece : public QObject
{
Q_OBJECT
public:
    explicit TetrisPiece(QObject *parent=nullptr);
    virtual ~TetrisPiece();
    void createObject();
    void moveRight();
    void moveLeft();
    void moveDown();
    void rotate();
    std::vector<QPoint> getPieceCoords();
private:
    std::vector<QPoint> pieceCoords;

    const int step = 20;
};

#endif // TETRISPIECE_H
