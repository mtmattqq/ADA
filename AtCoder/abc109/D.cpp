#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

const int INF{0x3f3f3f3f};
const int DIR{4};

enum DIR {
    LEFT, UP, RIGHT, DOWN
};

class Position {
public:
    Position(int _row, int _col)
        : row(_row), col(_col) {}
    const int& get_row() const { return row;}
    const int& get_col() const { return col;}
    Position operator+(const Position &other) const;
    Position& operator+=(const Position &other);
    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
private:
    int row, col;
};

const Position NOT_FOUND(-1, -1);

Position Position::operator+(const Position &other) const {
    return Position(row + other.row, col + other.col);
}

Position& Position::operator+=(const Position &other) {
    row += other.row;
    col += other.col;
    return *this;
}

bool Position::operator==(const Position &other) const {
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream &out, const Position &pos) {
    out << pos.get_row() << " " << pos.get_col();
    return out;
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
    int& operator[](Position pos);
    void operator=(Matrix &&other);
    bool contain(const Position &pos);
    Position size() { return Position(row, col);}
protected:
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
    for (int i{0}; i < row; ++i) {
        for (int j{0}; j < col; ++j) {
            in >> values[i][j];
        }
    }
}

int& Matrix::operator[](Position pos) {
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

class Board: public Matrix {
public:
    Board(int _row, int _col) : Matrix(_row, _col), push_count(0) {}
    void push_odd(Position start, Position end, int dir);
    const int& get_push_count() const { return push_count;}
    const std::vector<std::pair<Position, Position>>& get_moves() { return moves;};
private:
    int push_count;
    std::vector<std::pair<Position, Position>> moves;
};

void Board::push_odd(Position start, Position end, int dir) {
    for (Position cur{start}; cur + MOVEMENT[dir] != end; cur += MOVEMENT[dir]) {
        // 1101010101
        if (values[cur.get_row()][cur.get_col()] & 1) {
            moves.emplace_back(cur, cur + MOVEMENT[dir]);
            (*this)[cur]--;
            (*this)[cur + MOVEMENT[dir]]++;
            push_count++;
        }
    }
}

int main(void) {
    int H, W;
    std::cin >> H >> W;
    Board board(H, W);
    std::cin >> board;
    for (int i{0}; i < board.size().get_row(); ++i) {
        board.push_odd(Position(i, 0), Position(i, W - 1), RIGHT);
    }
    board.push_odd(Position(0, W - 1), Position(H, W - 1), DOWN);
    std::cout << board.get_push_count() << "\n";
    for (auto move : board.get_moves()) {
        std::cout << move.first + Position(1, 1) << " " 
                  << move.second + Position(1, 1) << "\n";
    }
}