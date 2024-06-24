#include <iostream>
#include <string>
#include <vector>

class Player {
public:
    Player(std::vector<std::string> _bat_results)
        : bat_results(_bat_results), current_result(0) {};
    std::string get_result() { return bat_results[current_result++];}
private:
    std::vector<std::string> bat_results;
    int current_result;
};

class BaseBags {
public:
    BaseBags() : has_player(3) {}
    int run(int num);
    void clear();
    std::vector<bool> has_player;
private:
};

int BaseBags::run(int num) {
    int ret{0};
    for (int i{0}; i < has_player.size(); i++) {
        if (i + num >= has_player.size() && has_player[i]) {
            has_player[i] = false;
            ret++;
        }
    }
    if (num == 4) {
        return ret + 1;
    }
    for (int i{int(has_player.size() - 1)}; i >= 0; i--) {
        if (i + num < has_player.size() && has_player[i])
            has_player[i + num] = true;
        has_player[i] = false;
    }
    has_player[num - 1] = true;
    return ret;
}

void BaseBags::clear() {
    for (int i{0}; i < has_player.size(); i++) {
        has_player[i] = false;
    }
}

class BaseBallGame {
public:
    BaseBallGame() : people(9), current_attacker(0), score(0), out_num(0) {};
    std::istream& input(std::istream &in);
    void attack();
    const int& get_score() { return score;}
    const int& get_outs() { return out_num;}
private:
    int people, current_attacker, score, out_num;
    std::vector<Player> players;
    BaseBags base_bags;
    void next_player() { current_attacker = (current_attacker + 1) % people;}
};

std::istream& BaseBallGame::input(std::istream &in) {
    players.clear();
    for (int i{0}; i < people; i++) {
        int bat_num;
        std::cin >> bat_num;
        std::vector<std::string> bat_results;
        for (int j{0}; j < bat_num; j++) {
            std::string bat_result;
            std::cin >> bat_result;
            bat_results.push_back(bat_result);
        }
        players.emplace_back(bat_results);
    }
    return in;
}

void BaseBallGame::attack() {
    std::string result{players[current_attacker].get_result()};
    next_player();
    if (result[1] == 'O') {
        out_num++;
        if (out_num % 3 == 0) {
            base_bags.clear();
        }
    }
    else if (result[1] == 'R') {
        score += base_bags.run(4);
    }
    else { // result[1] == 'B'
        score += base_bags.run(result[0] - '0');
    }
}

std::istream& operator>>(std::istream &in, BaseBallGame &game) {
    game.input(in);
    return in;
}

int main(void) {
    BaseBallGame game;
    std::cin >> game;
    int out_num;
    std::cin >> out_num;
    while (game.get_outs() < out_num) {
        game.attack();
    }
    std::cout << game.get_score() << "\n";
}