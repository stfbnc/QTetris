#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QColor>
#include <QPoint>

class DataManager : public QObject
{
Q_OBJECT
public:
    DataManager();
    ~DataManager();
    void setPieceColor(QColor c);
    QColor getPieceColor();
    void setPieceCoords(std::vector<QPoint> coords);
    std::vector<QPoint> getPieceCoords();
    void setBorders(int left, int right);
    int getRightBorder();
    int getLeftBorder();
signals:
    void updateBoard();
private:
    int leftBorder = 0;
    int rightBorder = 0;
    QColor color;
    std::vector<QPoint> pieceCoords;
};

#endif // DATAMANAGER_H
