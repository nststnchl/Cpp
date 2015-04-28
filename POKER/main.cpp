#include <iostream>
#include "deck.h"
#include "game.h"
#include "human_player.h"
#include "start_game.cpp"

using namespace std;

int main() {
    TextUI* ui = new TextUI(false);
    TexasHoldem* game = createGame((int)2, (int)100, (int) 10, ui,
            new HumanPlayer("First player", ui), new HumanPlayer("Second player", ui));
    game->run();
    delete game;
    return 0;
}
