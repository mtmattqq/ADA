#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using vec = std::vector<int>;
using mat = std::vector<vec>;

const int INF{0x3f3f3f3f};
const int DIR{4};

class Position {
public:
    Position(int _row, int _col)
        : row(_row), col(_col) {}
    const int& get_row() const { return row;}
    const int& get_col() const { return col;}
    Position operator+(const Position &other);
    bool operator==(const Position &other);
private:
    int row, col;
};

const Position NOT_FOUND(-1, -1);

Position Position::operator+(const Position &other) {
    return Position(row + other.row, col + other.col);
}

bool Position::operator==(const Position &other) {
    return row == other.row && col == other.col;
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
    const int& operator[](Position pos);
    void operator=(Matrix && other);
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

class Map: public Matrix {
public:
    Map(int _row, int _col)
        : Matrix(_row, _col), visited(_row, vec(_col)) {}
    int find_sum();
private:
    mat visited;
    Position find_min_pos();
};

Position Map::find_min_pos() {
    int min = INF;
    Position start_pos(0, 0);
    for (int i{0}; i < values.size(); ++i) {
        for (int j{0}; j < values[i].size(); ++j) {
            if (values[i][j] <= min) {
                start_pos = Position(i, j);
                min = values[i][j];
            }
        }
    }
    return start_pos;
}

int Map::find_sum() {
    int sum{0};
    Position current_pos{find_min_pos()};
    while (contain(current_pos)) {
        sum += (*this)[current_pos];
        visited[current_pos.get_row()][current_pos.get_col()] = true;
        int min = INF;
        Position try_pos{current_pos}, next_pos{NOT_FOUND};
        for (int i{0}; i < DIR; ++i) {
            try_pos = current_pos + MOVEMENT[i];
            if (!contain(try_pos)) {
                try_pos = current_pos;
                continue;
            }
            if (!visited[try_pos.get_row()][try_pos.get_col()] && (*this)[try_pos] < min) {
                min = (*this)[try_pos];
                next_pos = try_pos;
            }
        }
        if (next_pos == NOT_FOUND) {
            break;
        }
        else {
            current_pos = next_pos;
        }
    }
    return sum;
}

int main(void) {
    int n, m;
    std::cin >> n >> m;
    Map map(n, m);
    std::cin >> map;
    std::cout << map.find_sum() << "\n";
}