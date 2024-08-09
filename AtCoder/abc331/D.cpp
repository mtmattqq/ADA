#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using i64 = int64_t;

struct SideMeal {
    i64 value;
    int index;
};

int main(void) {
    int n, m, l;
    std::cin >> n >> m >> l;
    std::vector<i64> a(n);
    std::vector<SideMeal> b(m);
    std::unordered_map<int, std::unordered_set<int>> not_offered_pair;

    for (auto &e : a) std::cin >> e;
    for (int i{0}; i < b.size(); ++i) {
        b[i].index = i;
        std::cin >> b[i].value;
    }
    
    std::sort(b.begin(), b.end(), [](SideMeal a, SideMeal b) -> bool {
        if (a.value != b.value) {
            return a.value > b.value;
        }
        return a.index < b.index;
    });

    for (int i{0}; i < l; ++i) {
        int c, d;
        std::cin >> c >> d;
        not_offered_pair[c - 1].insert(d - 1);
    }
    
    i64 most_expensive{0};
    for (int i{0}; i < a.size(); ++i) {
        for (int j{0}; j < b.size(); ++j) {
            if (a[i] + b[j].value < most_expensive) break;
            if (!not_offered_pair.count(i) || !not_offered_pair[i].count(b[j].index)) {
                most_expensive = std::max(most_expensive, a[i] + b[j].value);
                break;
            }
        }
    }
    std::cout << most_expensive << "\n";
}