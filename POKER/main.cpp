#include <iostream>
#include "deck.h"
#include "game.h"
#include "human_player.h"
#include "start_game.cpp"

using namespace std;

int main() {
    TextUI* ui = new TextUI(false);
    int cash, small_blind;
    cout << "Enter initial amount of cash for each player: ";
    cin >> cash;
    cout << "Enter small blind: ";
    cin >> small_blind;
    game* my_game = createGame(2, cash, small_blind, ui, new HumanPlayer("Player 1", ui),
            new HumanPlayer("Player 2", new TextUI(true)));
    my_game->run();
    delete my_game;
    return 0;
}
