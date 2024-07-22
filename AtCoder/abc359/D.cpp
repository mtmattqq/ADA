#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using vec = std::vector<int64_t>;
using mat = std::vector<vec>;
const int64_t NOT_FOUND{-1};
const int64_t MOD{998244353};

// One can be another
bool can_be(char one, char another) {
    return one == '?' || one == another;
}

int to_index(const std::string &s) {
    int index{0};
    for (int i{0}; i < s.size(); ++i) {
        index = (index << 1) + (s[i] == 'B');
    }
    return index;
}

bool palindrome(const std::string &s, int left, int right) {
    for (int i{0}; i <= (right - left) / 2; ++i) {
        if (s[i + left] != s[right - i - 1]) {
            return false;
        }
    }
    return true;
}

int64_t count_not_palindrom(const std::string &s, mat &dp, int n, int k, int now, std::string &selected_substr) {
    // std::cout << selected_substr << "\n";
    // std::cout << "now: " << now << " k: " << k << "\n";
    if (now >= k && palindrome(selected_substr, now - k, now)) {
        // std::cout << "end with pal\n";
        return 0;
    }
    if (now == n) {
        return 1;
    }
    if (now >= k && dp[to_index(selected_substr.substr(now - k))][now] != NOT_FOUND) {
        return dp[to_index(selected_substr.substr(now - k))][now];
    }
    int64_t ret{0};
    if (can_be(s[now], 'A')) {
        selected_substr += 'A';
        ret = (ret + count_not_palindrom(s, dp, n, k, now + 1, selected_substr)) % MOD;
        selected_substr.pop_back();
    }
    if (can_be(s[now], 'B')) {
        selected_substr += 'B';
        ret = (ret + count_not_palindrom(s, dp, n, k, now + 1, selected_substr)) % MOD;
        selected_substr.pop_back();
    }
    return dp[to_index(selected_substr.substr(std::max(0, now - k)))][now] = ret;
}

void test_palindrom() {
    assert(palindrome("abba", 0, 4) == true);
    assert(palindrome("aabb", 0, 4) == false);
    assert(palindrome("abab", 0, 4) == false);
    assert(palindrome("abaaab", 2, 6) == false);
    assert(palindrome("abaaaba", 3, 7) == false);
}

int main(void) {
    test_palindrom();
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    mat dp((1 << k), vec(s.size(), NOT_FOUND));
    std::string selected_substr;
    std::cout << count_not_palindrom(s, dp, n, k, 0, selected_substr) << "\n";
}