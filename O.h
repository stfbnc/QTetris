#ifndef O_H
#define O_H

#include <tetrispiece.h>

class O : public TetrisPiece
{
Q_OBJECT
public:
    explicit O();
    ~O();
    O* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // O_H
