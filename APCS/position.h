#ifndef POSITION
#define POSITION

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

inline Position& Position::operator+=(const Position &other) {
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

#endif