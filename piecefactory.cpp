#include "piecefactory.h"

const std::map<int, QString> PieceFactory::piecesMap = {
    {0, "O"},
    {1, "L"},
    {2, "J"},
    {3, "S"},
    {4, "Z"},
    {5, "I"},
    {6, "T"}
};

TetrisPiece* PieceFactory::getRandomPiece()
{
    int num = getRandomNumber(0, piecesMap.size() - 1);
    QString piece = piecesMap.at(num);
    if(piece == "O")
        return new O{};
    else if(piece == "L")
        return new L{};
    else if(piece == "J")
        return new J{};
    else if(piece == "S")
        return new S{};
    else if(piece == "Z")
        return new Z{};
    else if(piece == "I")
        return new I{};
    else if(piece == "T")
        return new T{};
    else
        return new I{};
}

int PieceFactory::getRandomNumber(int min, int max)
{
    static constexpr double fraction{1.0 / (RAND_MAX + 1.0)};
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
