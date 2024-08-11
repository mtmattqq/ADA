#include <algorithm>
#include <iostream>
#include <vector>

const int INF = 0x3f3f3f3f;

struct Magic {
    int damage, cost;
};

int main(void) {
    int h, n;
    std::cin >> h >> n;
    std::vector<Magic> magics(n + 1);
    for (int i{1}; i <= n; ++i) {
        std::cin >> magics[i].damage >> magics[i].cost;
    }
    std::vector<int> dp[2]{std::vector<int>(h + 1), std::vector<int>(h + 1)};
    for (int i{1}; i <= h; ++i) {
        dp[0][i] = dp[1][i] = INF;
    }

    for (int i{1}; i <= n; ++i) {
        for (int j{1}; j <= h; ++j) {
            if (magics[i].damage >= j) {
                dp[i & 1][j] = std::min(dp[i & 1 ^ 1][j], magics[i].cost);
            }
            else {
                dp[i & 1][j] = std::min({
                    dp[i & 1 ^ 1][j], 
                    dp[i & 1 ^ 1][j - magics[i].damage] + magics[i].cost, 
                    dp[i & 1][j - magics[i].damage] + magics[i].cost});
            }
        }
    }
    std::cout << dp[n & 1][h] << "\n";
}