#include <iostream>
#include <string>
#include <vector>

struct Player {
    Player(std::vector<std::string> _bat_results)
        : bat_results(_bat_results), current_result(0) {};
    std::vector<std::string> bat_results;
    int current_result;
};

std::string get_result(Player &player) {
    return player.bat_results[player.current_result++];
}

struct BaseBags {
    BaseBags() : has_player(3) {}
    std::vector<bool> has_player;
};

int run(BaseBags &bags, int num) {
    int ret{0};
    for (int i{0}; i < bags.has_player.size(); i++) {
        if (i + num >= bags.has_player.size() && bags.has_player[i]) {
            bags.has_player[i] = false;
            ret++;
        }
    }
    if (num == 4) {
        return ret + 1;
    }
    for (int i{int(bags.has_player.size() - 1)}; i >= 0; i--) {
        if (i + num < bags.has_player.size() && bags.has_player[i])
            bags.has_player[i + num] = true;
        bags.has_player[i] = false;
    }
    bags.has_player[num - 1] = true;
    return ret;
}

void clear(BaseBags &bags) {
    for (int i{0}; i < bags.has_player.size(); i++) {
        bags.has_player[i] = false;
    }
}

struct BaseBallGame {
    BaseBallGame() : people(9), current_attacker(0), score(0), out_num(0) {};
    int people, current_attacker, score, out_num;
    std::vector<Player> players;
    BaseBags base_bags;
};

void next_player(BaseBallGame &game) {
    game.current_attacker = (game.current_attacker + 1) % game.people;
}

void input(std::istream &in, BaseBallGame &game) {
    game.players.clear();
    for (int i{0}; i < game.people; i++) {
        int bat_num;
        std::cin >> bat_num;
        std::vector<std::string> bat_results;
        for (int j{0}; j < bat_num; j++) {
            std::string bat_result;
            std::cin >> bat_result;
            bat_results.push_back(bat_result);
        }
        game.players.emplace_back(bat_results);
    }
}

void attack(BaseBallGame &game) {
    std::string result{get_result(game.players[game.current_attacker])};
    next_player(game);
    if (result[1] == 'O') {
        game.out_num++;
        if (game.out_num % 3 == 0) {
            clear(game.base_bags);
        }
    }
    else if (result[1] == 'R') {
        game.score += run(game.base_bags, 4);
    }
    else { // result[1] == 'B'
        game.score += run(game.base_bags, result[0] - '0');
    }
}

int main(void) {
    BaseBallGame game;
    input(std::cin, game);
    int out_num;
    std::cin >> out_num;
    while (game.out_num < out_num) {
        attack(game);
    }
    std::cout << game.score << "\n";
}