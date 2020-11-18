#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QFrame>
#include <QPainter>
#include <QColor>
#include "defines.h"
#include "datamanager.h"

class Board : public QFrame
{
Q_OBJECT
public:
    explicit Board(QWidget *parent=nullptr);
    virtual ~Board();
    void setDataManager(DataManager *dm);
private slots:
    void updateBoard();
private:
    void paintEvent(QPaintEvent *e) override;

    const int m_innerSquareSize = 8;
    DataManager *dataManager;
};

#endif // BOARD_H
