#ifndef Z_H
#define Z_H

#include <tetrispiece.h>

class Z : public TetrisPiece
{
Q_OBJECT
public:
    explicit Z();
    ~Z();
    Z* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // Z_H
