#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <cstdint>

const int NOT_FOUND{-1};
const int64_t EMPTY{2};

class StoneSet {
public:
    StoneSet(int64_t _stones, int _n, int _step = 0)
        : stones(_stones), n(_n), step(_step) {}
    static int64_t str_to_stone(const std::string &s);
    const int64_t& get_stones() const { return stones;}
    const int& get_step() const { return step;}
    const int& get_n() const { return n;}
    StoneSet& swap(int a);
    int get_empty();
    int64_t get(int p);
    bool operator<(StoneSet other) const;
private:
    void set(int p, int64_t val);
    int64_t stones;
    int n, step;
};

//* 0  1  2  3  4  
//* 1  4  16 64 256
int64_t StoneSet::str_to_stone(const std::string &s) {
    int64_t ret_stones{0};
    for (int i{0}; i < s.size(); ++i) {
        ret_stones += (s[i] == 'W') << (2 * i);
    }
    ret_stones += EMPTY << (2 * s.size());
    ret_stones += EMPTY << (2 * (s.size() + 1));
    return ret_stones;
}

bool StoneSet::operator<(StoneSet other) const {
    return stones < other.stones;
}

int StoneSet::get_empty() {
    int empty_space{0};
    for (int i{0}; i < n; ++i) {
        if (get(i) == EMPTY) {
            empty_space = i;
            break;
        }
    }
    return empty_space;
}

StoneSet& StoneSet::swap(int a) {
    int empty_space{get_empty()};
    set(empty_space, get(a));
    set(empty_space + 1, get(a + 1));
    set(a, EMPTY);
    set(a + 1, EMPTY);
    step++;
    return *this;
}

int64_t StoneSet::get(int p) {
    return (stones >> (p * 2)) & 3;
}

void StoneSet::set(int p, int64_t val) {
    stones &= ~(3LL << (2 * p));
    stones |= val << (2 * p);
}

int find_min_step(const std::string &s, const std::string &t) {
    StoneSet start(StoneSet::str_to_stone(s), s.size() + 2);
    int64_t target{StoneSet::str_to_stone(t)};
    std::queue<StoneSet> q;
    std::set<StoneSet> used_pattern;
    q.push(start);
    used_pattern.insert(start);
    while (!q.empty()) {
        StoneSet now{q.front()};
        q.pop();
        if (now.get_stones() == target) {
            return now.get_step();
        }
        for (int i{0}, empty_space{now.get_empty()}; i < now.get_n() - 1; ++i) {
            if (now.get(i) != EMPTY && now.get(i + 1) != EMPTY) {
                auto next {now};
                next.swap(i);
                if (!used_pattern.count(next)) {
                    used_pattern.insert(next);
                    q.push(next);
                }
            }
        }
    }
    return NOT_FOUND;
}

int count_white(const std::string &s) {
    int ct{0};
    for (int i{0}; i < s.size(); ++i) {
        if (s[i] == 'W') {
            ct++;
        }
    }
    return ct;
}

int main(void) {
    int n;
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    if (count_white(s) == count_white(t)) {
        std::cout << find_min_step(s, t) << "\n";
    }
    else {
        std::cout << NOT_FOUND << "\n";
    }
}