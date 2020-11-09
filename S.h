#ifndef S_H
#define S_H

#include <tetrispiece.h>

class S : public TetrisPiece
{
Q_OBJECT
public:
    explicit S();
    ~S();
    void initialize() override;
    void rotate() override;
};

#endif // S_H
