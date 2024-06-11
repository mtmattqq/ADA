// b965
#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

class Position {
public:
    Position(int _row, int _col)
        : row(_row), col(_col) {}
private:
    int row, col;
};

class Matrix {
public:
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    void input(std::istream &in);
    void output(std::ostream &out);
    const int& operator[](Position pos);
    void operator=(Matrix &&other);
private:
    mat values;
    int row, col;
};

void Matrix::operator=(Matrix &&other) {
    values = std::move(other.values);
    row = other.row;
    col = other.col;
    other.row = other.col = 0;
}

void Matrix::input(std::istream &in) {
    for (int i{0}; i < row; i++) {
        for (int j{0}; j < col; j++) {
            in >> values[i][j];
        }
    }
}

void Matrix::output(std::ostream &out) {
    out << row << " " << col << "\n";
    for (int i{0}; i < row; i++) {
        for (int j{0}; j < col; j++) {
            out << values[i][j] << " \n"[j == col - 1];
        }
    }
}

std::istream& operator>>(std::istream &in, Matrix &m) {
    m.input(in);
    return in;
}

std::ostream& operator<<(std::ostream &out, Matrix &m) {
    m.output(out);
    return out;
}

int main(void) {
    ;
}