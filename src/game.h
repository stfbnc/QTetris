#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QThread>
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

    Game(int s, DataManager *dm, int nGames);
    ~Game();
    void move(MOVES direction);
    void setGames(int games);
    void resetGames();
public slots:
    void setSpeed(int speed);
    void resumeGame();
    void playAgain();
    void stopGame();
    void startGame();
    void updateGame();
signals:
    void endGame();
private:
    void newPiece();
    void deletePiece();
    bool canMove(MOVES direction);

    int maxGames;
    int gameCount;
    bool running;
    bool moving;
    int speed;
    QTimer *timer;
    TetrisPiece *currentPiece;
    DataManager *dataManager;
};

#endif // GAME_H
