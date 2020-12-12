#ifndef I_H
#define I_H

#include <tetrispiece.h>

class I : public TetrisPiece
{
Q_OBJECT
public:
    explicit I();
    ~I();
    I* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // I_H
