#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include "piecefactory.h"
#include "datamanager.h"

class Game : public QObject
{
Q_OBJECT
public:
    enum MOVES
    {
        RIGHT,
        LEFT,
        DOWN,
        DOWN_FAST,
        ROTATE
    };

    Game(int s, DataManager *dm);
    ~Game();
    void move(MOVES direction);
public slots:
    void setSpeed(int speed);
    void resumeGame();
    void stopGame();
    void startGame();
    void updateGame();
private:
    void newPiece();
    bool canMove(MOVES direction);

    int speed;
    QTimer *timer;
    TetrisPiece *currentPiece;
    DataManager *dataManager;
};

#endif // GAME_H
