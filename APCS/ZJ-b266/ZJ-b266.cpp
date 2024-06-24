// b965
#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

class Matrix {
public:
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    void input(std::istream &in);
    void output(std::ostream &out);
    void left_rotate();
    // void right_rotate();
    void flip();
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

void Matrix::left_rotate() {
    Matrix temp(col, row);
    for (int i{0}; i < row; i++) {
        for (int j{0}; j < col; j++) {
            temp.values[col - j - 1][i] = values[i][j];
        }
    }
    *this = std::move(temp);
}

void Matrix::flip() {
    for (int i{0}; i < (row >> 1); i++) {
        for (int j{0}; j < col; j++) {
            std::swap(values[i][j], values[row - i - 1][j]);
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
    int r, c, m;
    std::cin >> r >> c >> m;
    Matrix matrix(r, c);
    std::cin >> matrix;
    vec ops(m);
    for (auto &e : ops) {
        std::cin >> e;
    }
    for (int i{m - 1}; i >= 0; i--) {
        switch (ops[i]) {
        case 0:
            matrix.left_rotate();
            break;
        case 1:
            matrix.flip();
            break;
        }
    }
    std::cout << matrix;
}