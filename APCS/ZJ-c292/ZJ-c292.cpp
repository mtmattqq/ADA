#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

enum DIR {
    LEFT, UP, RIGHT, DOWN
};

class Position {
public:
    Position(int _row, int _col)
        : row(_row), col(_col) {}
    const int& get_row() const { return row;}
    const int& get_col() const { return col;}
    Position& operator+=(const Position &other);
private:
    int row, col;
};

Position& Position::operator+=(const Position &other) {
    row += other.row;
    col += other.col;
    return *this;
}

const Position MOVEMENT[] {
    Position(0, -1),
    Position(-1, 0),
    Position(0, 1),
    Position(1, 0)
};

class Matrix {
public:
    Matrix(int _row, int _col)
        : row(_row), col(_col), values(_row, vec(_col)) {}
    void input(std::istream &in);
    void output(std::ostream &out);
    const int& operator[](Position pos);
    void operator=(Matrix &&other);
    bool contain(const Position &pos);
    Position size() { return Position(row, col);}
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

void change_dir(int &dir) {
    dir = (dir + 1) % 4;
}

void print_board(Matrix &board, Position pos_now, int dir) {
    for (int i{0}; i < board.size().get_row(); i++) {
        for (int j{0}; j < 2; j++) {
            for (int k{0}; k <= i; k++) {
                if (board.contain(pos_now)) {
                    std::cout << board[pos_now];
                    pos_now += MOVEMENT[dir];
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
    std::cin >> board;
    Position start_pos(n / 2, n / 2);
    print_board(board, start_pos, start_dir);
}