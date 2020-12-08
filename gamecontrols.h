#ifndef GAMECONTROLS_H
#define GAMECONTROLS_H

#include <QWidget>
#include <QKeySequence>
#include <QDebug>

namespace Ui {
    class GameControls;
}

class GameControls : public QWidget
{
Q_OBJECT
public:
    explicit GameControls(QKeySequence r1, QKeySequence l1, QKeySequence d1, QKeySequence rot1,
                          QKeySequence r2, QKeySequence l2, QKeySequence d2, QKeySequence rot2,
                          QWidget *parent=nullptr);
    ~GameControls();
    QKeySequence getPlayer1RightKey();
    QKeySequence getPlayer1LeftKey();
    QKeySequence getPlayer1DownKey();
    QKeySequence getPlayer1RotateKey();
    QKeySequence getPlayer2RightKey();
    QKeySequence getPlayer2LeftKey();
    QKeySequence getPlayer2DownKey();
    QKeySequence getPlayer2RotateKey();
signals:
    void okPressed(QKeySequence, QKeySequence, QKeySequence, QKeySequence,
                   QKeySequence, QKeySequence, QKeySequence, QKeySequence);
private slots:
    void onCancelButton();
    void onOkButton();
private:
    Ui::GameControls *ui;

    QKeySequence right1;
    QKeySequence left1;
    QKeySequence down1;
    QKeySequence rotate1;
    QKeySequence right2;
    QKeySequence left2;
    QKeySequence down2;
    QKeySequence rotate2;
};

#endif // GAMECONTROLS_H
