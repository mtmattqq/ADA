#include <iostream>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

enum DIR {
    LEFT, UP, RIGHT, DOWN
};

struct Position {
    Position(int _row, int _col)
        : row(_row), col(_col) {}
    int row, col;
};

Position& add_equal(Position &one, const Position &other) {
    one.row += other.row;
    one.col += other.col;
    return one;
}

const Position MOVEMENT[] {
    Position(0, -1),
    Position(-1, 0),
    Position(0, 1),
    Position(1, 0)
};

struct Matrix {
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    const int& operator[](Position pos);
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

int get_cell(Matrix &matrix, Position pos) {
    return matrix.values[pos.row][pos.col];
}

bool contain(Matrix &matrix, const Position &pos) {
    return pos.row >= 0 && pos.row < matrix.row &&
        pos.col >= 0 && pos.col < matrix.col;
}

Position size(Matrix &matrix) {
    return Position(matrix.row, matrix.col);
}

void change_dir(int &dir) {
    dir = (dir + 1) % 4;
}

void print_board(Matrix &board, Position pos_now, int dir) {
    for (int i{0}; i < size(board).row; i++) {
        for (int j{0}; j < 2; j++) {
            for (int k{0}; k <= i; k++) {
                if (contain(board, pos_now)) {
                    std::cout << board[pos_now];
                    add_equal(pos_now, MOVEMENT[dir]);
                }
                else {
                    return;
                }
            }
            change_dir(dir);
        }
    }
}

int main(void) {
    int n, start_dir;
    std::cin >> n >> start_dir;
    Matrix board(n, n);
    input(std::cin, board);
    Position start_pos(n / 2, n / 2);
    print_board(board, start_pos, start_dir);
}