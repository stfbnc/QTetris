#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <QObject>
#include <QColor>
#include <QPoint>
#include <QSound>
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
    void resetScores();
    const std::map<std::pair<int, int>, QColor> getBoardMap();
    void addPoints(int p);
    void increaseGameCount();
signals:
    void updateBoard();
    void lineCleared();
    void swapLines(std::map<std::pair<int, int>, QColor>, int);
    void gameCount(int);
    void updatePoints(int, int, int);
public slots:
    void addSwapLines(std::map<std::pair<int, int>, QColor> swap, int nSwap);
private:
    void removeLine(int line);
    void addLineToSwap(int line, int lineIdx);

    int leftBorder = 0;
    int rightBorder = 0;
    int bottomBorder = 0;
    int points = 0;
    int lines = 0;
    int swaps = 0;
    int games = 1;
    QColor color;
    std::vector<QPoint> pieceCoords = std::vector<QPoint>();
    std::map<std::pair<int, int>, QColor> boardMap = std::map<std::pair<int, int>, QColor>();
    std::map<std::pair<int, int>, QColor> swapPieces = std::map<std::pair<int, int>, QColor>();
};

#endif // DATAMANAGER_H
