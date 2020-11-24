#ifndef L_H
#define L_H

#include <tetrispiece.h>

class L : public TetrisPiece
{
Q_OBJECT
public:
    explicit L();
    ~L();
    L* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // L_H
