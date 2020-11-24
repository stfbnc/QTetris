#ifndef T_H
#define T_H

#include <tetrispiece.h>

class T : public TetrisPiece
{
Q_OBJECT
public:
    explicit T();
    ~T();
    T* clone() const override;
    void initialize() override;
    void rotate() override;
};

#endif // T_H
