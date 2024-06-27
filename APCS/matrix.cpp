#include "matrix.h"

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

const int& Matrix::operator[](Position pos) {
    return values[pos.get_row()][pos.get_col()];
}

bool Matrix::contain(const Position &pos) {
    return pos.get_row() >= 0 && pos.get_row() < row &&
        pos.get_col() >= 0 && pos.get_col() < col;
}

std::istream& operator>>(std::istream &in, Matrix &m) {
    m.input(in);
    return in;
}

std::ostream& operator<<(std::ostream &out, Matrix &m) {
    m.output(out);
    return out;
}