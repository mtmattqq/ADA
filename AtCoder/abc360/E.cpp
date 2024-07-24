#include <cstdint>
#include <iostream>

class ModInt {
public:
    ModInt(int64_t _value = 0) : value(_value) {}
    ModInt& operator+=(const ModInt &other);
    ModInt& operator-=(const ModInt &other);
    ModInt& operator*=(const ModInt &other);
    ModInt& operator/=(const ModInt &other);
    ModInt operator+(const ModInt &other) const;
    ModInt operator-(const ModInt &other) const;
    ModInt operator*(const ModInt &other) const;
    ModInt operator/(const ModInt &other) const;
    bool operator==(const ModInt &other) const { return value == other.value;}
    void print(std::ostream &out);
    void input(std::istream &in);
    const static int64_t MOD{998244353};
private:
    int64_t pow(int64_t a, int64_t x);
    int64_t value;
};

int64_t ModInt::pow(int64_t a, int64_t x) {
    int64_t ret{1};
    while (x > 0) {
        if (x & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        x >>= 1;
    }
    return ret;
}

ModInt& ModInt::operator+=(const ModInt &other) {
    value = (value + other.value) % MOD;
    return *this;
}

ModInt& ModInt::operator-=(const ModInt &other) {
    value = (value - other.value + MOD) % MOD;
    return *this;
}

ModInt& ModInt::operator*=(const ModInt &other) {
    value = (value * other.value) % MOD;
    return *this;
}

ModInt& ModInt::operator/=(const ModInt &other) {
    value = (value * pow(other.value, MOD - 2)) % MOD;
    return *this;
}

ModInt ModInt::operator+(const ModInt &other) const {
    ModInt ret{*this};
    ret += other;
    return ret;
}

ModInt ModInt::operator-(const ModInt &other) const {
    ModInt ret{*this};
    ret -= other;
    return ret;
}

ModInt ModInt::operator*(const ModInt &other) const {
    ModInt ret{*this};
    ret *= other;
    return ret;
}

ModInt ModInt::operator/(const ModInt &other) const {
    ModInt ret{*this};
    ret /= other;
    return ret;
}

void ModInt::print(std::ostream &out) {
    out << value;
}

void ModInt::input(std::istream &in) {
    in >> value;
    value = ((value % MOD) + MOD) % MOD;
}

std::ostream& operator<<(std::ostream &out, ModInt num) {
    num.print(out);
    return out;
}

std::istream& operator>>(std::istream &in, ModInt num) {
    num.input(in);
    return in;
}

int main(void) {
    int64_t n, k;
    std::cin >> n >> k;
    ModInt expect_pos(1);
    const ModInt pos_sum(ModInt(n) * ModInt(n + 1) / ModInt(2));
    for (int i{0}; i < k; ++i) {
        const ModInt choosed{ModInt(1) / ModInt(n)};
        const ModInt not_choosed{ModInt(n - 1) / ModInt(n)};
        const ModInt stay_inplace{expect_pos * (ModInt(1) - choosed * not_choosed * 2)};
        const ModInt move_elsewhere{(pos_sum - expect_pos) / ModInt(n - 1) * choosed * not_choosed * ModInt(2)};
        expect_pos = stay_inplace + move_elsewhere;
    }
    std::cout << expect_pos << "\n";
}