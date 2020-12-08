#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QKeyEvent>
#include <QThread>
#include <QInputDialog>
#include "board.h"
#include "datamanager.h"
#include "game.h"
#include "gamecontrols.h"

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    virtual ~MainWindow();
signals:
    void stopGame();
    void resumeGame();
    void playAgain();
    void speedChanged(int speed);
private slots:
    void openControls();
    void setControls(QKeySequence r1, QKeySequence l1, QKeySequence d1, QKeySequence rot1,
                     QKeySequence r2, QKeySequence l2, QKeySequence d2, QKeySequence rot2);
    void setGames();
    void startGame();
    void pauseGame();
    void resetGame();
private:
    void setDarkTheme();
    void createConnections();
    void initializeGame();
    void setStartingPoints();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    Ui::MainWindow *ui;
    QThread* thread1;
    QThread* thread2;
    Game *game1 = nullptr;
    Game *game2 = nullptr;
    DataManager *gameData1 = nullptr;
    DataManager *gameData2 = nullptr;
    bool running;
    bool isFirstGame;
    int nGames;
    QKeySequence right1 = QKeySequence(Qt::Key_D);
    QKeySequence left1 = QKeySequence(Qt::Key_A);
    QKeySequence down1 = QKeySequence(Qt::Key_X);
    QKeySequence rotate1 = QKeySequence(Qt::Key_S);
    QKeySequence right2 = QKeySequence(Qt::Key_Right);
    QKeySequence left2 = QKeySequence(Qt::Key_Left);
    QKeySequence down2 = QKeySequence(Qt::Key_Down);
    QKeySequence rotate2 = QKeySequence(Qt::Key_Up);

    enum SPEED
    {
        VERY_SLOW = 1000,
        SLOW = 500,
        NORMAL = 250,
        FAST = 125,
        VERY_FAST = 50
    };
};
#endif // MAINWINDOW_H
