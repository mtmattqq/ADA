#include <iostream>
#include <utility>
#include <vector>

enum DIR {
    LEFT, UP, RIGHT, DOWN
};

class Position {
public:
    Position(int _row, int _col)
        : row(_row), col(_col) {}
    const int& get_row() const { return row;}
    const int& get_col() const { return col;}
    Position& add_equal(const Position &other);
private:
    int row, col;
};

inline Position& Position::add_equal(const Position &other) {
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
    int& operator[](Position pos);
    bool contain(const Position &pos);
    Position size() { return Position(row, col);}
    int count(int num);
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

int& Matrix::operator[](Position pos) {
    return values[pos.get_row()][pos.get_col()];
}

bool Matrix::contain(const Position &pos) {
    return pos.get_row() >= 0 && pos.get_row() < row &&
        pos.get_col() >= 0 && pos.get_col() < col;
}

int Matrix::count(int num) {
    int ret{0};
    for (int i{0}; i < row; ++i) {
        for (int j{0}; j < col; ++j) {
            ret += (values[i][j] == num);
        }
    }
    return ret;
}

std::istream& operator>>(std::istream &in, Matrix &m) {
    m.input(in);
    return in;
}

std::ostream& operator<<(std::ostream &out, Matrix &m) {
    m.output(out);
    return out;
}

class Boss {
public:
    Boss(Position _pos_now, Position _move_speed)
        : pos_now(_pos_now), move_speed(_move_speed), alive(true) {}
    void move() { pos_now.add_equal(move_speed);}
    bool is_alive() { return alive;}
    void disappear() { alive = false;}
    Position get_pos() { return pos_now;}
private:
    Position pos_now, move_speed;
    bool alive;
};

void simulate_boss_move(Matrix &bombs, std::vector<Boss> &bosses) {
    while (!bosses.empty()) {
        for (auto &boss : bosses) {
            bombs[boss.get_pos()] = 1;
            boss.move();
        }
        for (auto &boss : bosses) {
            if (bombs.contain(boss.get_pos()) && bombs[boss.get_pos()] == 1) {
                boss.disappear();
            }
        }
        std::vector<Boss> remain_bosses;
        for (auto boss : bosses) {
            if (boss.is_alive() && bombs.contain(boss.get_pos())) {
                remain_bosses.push_back(boss);
            }
            else if (bombs.contain(boss.get_pos())) {
                bombs[boss.get_pos()] = 0;
            }
        }
        bosses = std::move(remain_bosses);
    }
    std::cout << bombs.count(1) << "\n";
}

int main(void) {
    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix bombs(n, m);
    std::vector<Boss> bosses;
    for (int i{0}; i < k; ++i) {
        int r, c, s, t;
        std::cin >> r >> c >> s >> t;
        bosses.emplace_back(Position(r, c), Position(s, t));
    }
    simulate_boss_move(bombs, bosses);
}