#include "datamanager.h"

DataManager::DataManager()
{
    setBorders(0, MAXW, MAXH);
    initializeMap();
}

DataManager::~DataManager()
{
}

void DataManager::setPieceColor(QColor c)
{
    color = c;
}

const QColor DataManager::getPieceColor()
{
    return color;
}

void DataManager::setPieceCoords(std::vector<QPoint> coords)
{
    pieceCoords = coords;
    emit updateBoard();
}

void DataManager::addPieceToBoard()
{
    swapPieces.clear();
    int nFullLines = 0;

    for(QPoint p : pieceCoords)
    {
        if(p.y() >= 0)
            boardMap[std::pair<int, int>(p.x(), p.y())] = color;
    }

    for(int i = 0; i < MAXH; i += STEP)
    {
        bool lineFull = true;
        for(int j = 0; j < MAXW; j += STEP)
        {
            if(boardMap[std::pair<int, int>(j, i)] == Qt::transparent)
            {
                lineFull = false;
                break;
            }
        }
        if(lineFull)
        {
            addLineToSwap(i, nFullLines);
            removeLine(i);
            nFullLines++;
            lines++;
            points += FULL_LINE_POINTS;
        }
    }
    emit updateBoard();

    if(nFullLines > 1)
    {
        swaps += nFullLines;
        points += (nFullLines * SWAP_LINE_POINTS);
        qRegisterMetaType<std::map<std::pair<int, int>, QColor>>("std::map<std::pair<int, int>, QColor>");
        emit swapLines(swapPieces, nFullLines);
    }

    emit updatePoints(points, lines, swaps);
}

const std::vector<QPoint> DataManager::getPieceCoords()
{
    return pieceCoords;
}

void DataManager::setBorders(int left, int right, int bottom)
{
    leftBorder = left;
    rightBorder = right;
    bottomBorder = bottom;
}

int DataManager::getRightBorder()
{
    return rightBorder;
}

int DataManager::getLeftBorder()
{
    return leftBorder;
}

int DataManager::getBottomBorder()
{
    return bottomBorder;
}

void DataManager::initializeMap()
{
    for(int i = 0; i < MAXW; i += STEP)
    {
        for(int j = 0; j < MAXH; j += STEP)
        {
            boardMap[std::pair<int, int>(i, j)] = Qt::transparent;
        }
    }
}

void DataManager::resetScores()
{
    points = 0;
    lines = 0;
    swaps = 0;
    games = 1;
}

const std::map<std::pair<int, int>, QColor> DataManager::getBoardMap()
{
    return boardMap;
}

void DataManager::addPoints(int p)
{
    points += p;
}

void DataManager::increaseGameCount()
{
    games++;
    emit gameCount(games);
}

void DataManager::addSwapLines(std::map<std::pair<int, int>, QColor> swap, int nSwap)
{
    for(QPoint &p : pieceCoords)
        p -= QPoint(0, nSwap * STEP);

    for(int j = 0; j < MAXW; j += STEP)
    {
        for(int i = nSwap * STEP; i < MAXH; i += STEP)
            boardMap[std::pair<int, int>(j, i - nSwap * STEP)] = boardMap[std::pair<int, int>(j, i)];
    }

    for(int i = 0; i < nSwap; i++)
    {
        for(int j = 0; j < MAXW; j += STEP)
            boardMap[std::pair<int, int>(j, MAXH - (nSwap - i) * STEP)] = swap[std::pair<int, int>(j, MAXH - (i + 1) * STEP)];
    }

    emit updateBoard();
}

void DataManager::removeLine(int line)
{
    for(int j = 0; j < MAXW; j += STEP)
    {
        for(int i = line; i >= STEP; i -= STEP)
            boardMap[std::pair<int, int>(j, i)] = boardMap[std::pair<int, int>(j, i - STEP)];
        boardMap[std::pair<int, int>(j, 0)] = Qt::transparent;
    }
}

void DataManager::addLineToSwap(int line, int lineIdx)
{
    std::vector<int> lastPieceInLine = std::vector<int>();
    for(QPoint p : pieceCoords)
    {
        if(p.y() == line)
            lastPieceInLine.push_back(p.x());
    }

    for(int j = 0; j < MAXW; j += STEP)
    {
        if(std::find(lastPieceInLine.begin(), lastPieceInLine.end(), j) == lastPieceInLine.end())
            swapPieces[std::pair<int, int>(j, MAXH - (lineIdx + 1) * STEP)] = boardMap[std::pair<int, int>(j, line)];
        else
            swapPieces[std::pair<int, int>(j, MAXH - (lineIdx + 1) * STEP)] = Qt::transparent;
    }
}
