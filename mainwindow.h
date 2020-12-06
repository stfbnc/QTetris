#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QKeyEvent>
#include <QThread>
#include "board.h"
#include "datamanager.h"
#include "game.h"

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
    void startGame();
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
    Game *game1;
    Game *game2;
    DataManager *gameData1;
    DataManager *gameData2;
    bool running;
    bool isFirstGame;
    int nGames;

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
