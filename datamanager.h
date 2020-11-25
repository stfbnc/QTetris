#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <QObject>
#include <QColor>
#include <QPoint>
#include "defines.h"

class DataManager : public QObject
{
Q_OBJECT
public:
    DataManager();
    ~DataManager();
    void setPieceColor(QColor c);
    const QColor getPieceColor();
    void setPieceCoords(std::vector<QPoint> coords);
    void addPieceToBoard();
    const std::vector<QPoint> getPieceCoords();
    void setBorders(int left, int right, int bottom);
    int getRightBorder();
    int getLeftBorder();
    int getBottomBorder();
    void initializeMap();
    const std::map<std::pair<int, int>, QColor> getBoardMap();
signals:
    void updateBoard();
private:
    void removeLine(int line);

    int leftBorder = 0;
    int rightBorder = 0;
    int bottomBorder = 0;
    QColor color;
    std::vector<QPoint> pieceCoords = std::vector<QPoint>();
    std::map<std::pair<int, int>, QColor> boardMap = std::map<std::pair<int, int>, QColor>();
};

#endif // DATAMANAGER_H
