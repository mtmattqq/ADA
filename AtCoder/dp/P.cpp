#include <iostream>
#include <vector>
#include <functional>

const int64_t MOD = 1e9 + 7;

int main(void) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tree(n);
    for (int i{0}; i < n - 1; ++i) {
        int from, to;
        std::cin >> from >> to;
        tree[from - 1].push_back(to - 1);
        tree[to - 1].push_back(from - 1);
    }
    // * dp[0][x] := x is black
    // * dp[1][x] := x is white
    std::vector<int64_t> dp[2]{std::vector<int64_t>(n), std::vector<int64_t>(n)};

    std::function<void(int, int)> dfs = [&](int now, int parent) {
        dp[0][now] = dp[1][now] = 1;
        for (auto next : tree[now]) {
            if (next != parent) {
                dfs(next, now);
                dp[0][now] = (dp[0][now] * dp[1][next]) % MOD;
                dp[1][now] = (dp[1][now] * (dp[0][next] + dp[1][next])) % MOD;
            }
        }
    };

    dfs(0, 0);
    std::cout << (dp[0][0] + dp[1][0]) % MOD << "\n";
}