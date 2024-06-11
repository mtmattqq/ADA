#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    int N;
    std::cin >> N;
    std::vector<int> skewers(2 * N);
    for (auto &e : skewers) {
        std::cin >> e;
    }
    std::sort(skewers.begin(), skewers.end());
    int sum{0};
    for (int i{0}; i < skewers.size(); i += 2) {
        sum += skewers[i];
    }
    std::cout << sum << "\n";
}