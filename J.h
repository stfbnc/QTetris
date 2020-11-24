#ifndef J_H
#define J_H

#include <tetrispiece.h>

class J : public TetrisPiece
{
Q_OBJECT
public:
    explicit J();
    ~J();
    J* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // J_H
