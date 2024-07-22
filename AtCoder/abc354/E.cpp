#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const int NONE{-1};
const std::string ANS[2]{"Aoki", "Takahashi"};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i{0}; i < n; ++i) {
        std::cin >> a[i] >> b[i];
    }

    std::vector<bool> dp(1LL << n);
    for (int64_t i{1}; i < (1LL << n); ++i) {
        for (int j{0}; j < n; ++j) {
            if (!((i >> j) & 1)) continue;
            for (int k{j + 1}; k < n; ++k) {
                if (!((i >> k) & 1)) continue;
                if ((a[j] == a[k] || b[j] == b[k]) && (dp[i - (1LL << j) - (1LL << k)] == false)) {
                    dp[i] = true;
                }
            }
        }
    }
    std::cout << ANS[dp.back()] << "\n";
}