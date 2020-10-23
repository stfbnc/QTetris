#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "board.h"
#include "tetrispiece.h"

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
private:
    void startGame();
    void keyPressEvent(QKeyEvent *event);

    Ui::MainWindow *ui;
    QTimer *timer;
    TetrisPiece *currentPiece;

    enum SPEED
    {
        VERY_SLOW = 1000,
        SLOW = 500,
        NORMAL = 250,
        FAST = 125,
        VERY_FAST = 50
    };
private slots:
    void updateGame();
};
#endif // MAINWINDOW_H
