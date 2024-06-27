#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <utility>
#include <vector>
#include "position.h"

using vec = std::vector<int>;
using mat = std::vector<vec>;

class Matrix {
public:
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    void input(std::istream &in);
    void output(std::ostream &out);
    void left_rotate();
    void flip();
    void operator=(Matrix &&other);
    const int& operator[](Position pos);
    bool contain(const Position &pos);
    Position size() { return Position(row, col);}
private:
    mat values;
    int row, col;
};

#endif