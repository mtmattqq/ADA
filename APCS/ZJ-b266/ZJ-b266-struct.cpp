// b965
#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

struct Matrix {
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    mat values;
    int row, col;
};

void input(std::istream &in, Matrix &matrix) {
    for (int i{0}; i < matrix.row; i++) {
        for (int j{0}; j < matrix.col; j++) {
            in >> matrix.values[i][j];
        }
    }
}

void output(std::ostream &out, const Matrix &matrix) {
    out << matrix.row << " " << matrix.col << "\n";
    for (int i{0}; i < matrix.row; i++) {
        for (int j{0}; j < matrix.col; j++) {
            out << matrix.values[i][j] << " \n"[j == matrix.col - 1];
        }
    }
}

void left_rotate(Matrix &matrix) {
    Matrix temp(matrix.col, matrix.row);
    for (int i{0}; i < matrix.row; i++) {
        for (int j{0}; j < matrix.col; j++) {
            temp.values[matrix.col - j - 1][i] = matrix.values[i][j];
        }
    }
    matrix = temp;
}

void flip(Matrix &matrix) {
    for (int i{0}; i < (matrix.row >> 1); i++) {
        for (int j{0}; j < matrix.col; j++) {
            std::swap(matrix.values[i][j], matrix.values[matrix.row - i - 1][j]);
        }
    }
}

int main(void) {
    int r, c, m;
    std::cin >> r >> c >> m;
    Matrix matrix(r, c);
    input(std::cin, matrix);
    vec ops(m);
    for (auto &e : ops) {
        std::cin >> e;
    }
    for (int i{m - 1}; i >= 0; i--) {
        switch (ops[i]) {
        case 0:
            left_rotate(matrix);
            break;
        case 1:
            flip(matrix);
            break;
        }
    }
    output(std::cout, matrix);
}