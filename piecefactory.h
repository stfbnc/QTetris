#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <iostream>
#include <cstdlib>
#include "tetrispiece.h"
#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"

class PieceFactory
{
public:
    static TetrisPiece* getRandomPiece();
private:
    static int getRandomNumber(int min, int max);

    static const std::map<int, QString> piecesMap;
};

#endif // PIECEFACTORY_H
