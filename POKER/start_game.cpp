#include <algorithm>
#include <ctime>

#include "game.h"
#include "open_card.h"
#include "close_card.h"

template <class ... Players>
TexasHoldem* createGame(int n, int initCash, int smallBlind, TextUI* ui, Players* ... p) {
    TexasHoldem* result = new TexasHoldem();
    result->UI = ui;
    result->playersN = n;
    result->smallBlind = smallBlind;
    result->cl_deck = std::vector <close_card>();
    result->board = std::vector <open_card>();

    result->players = new TexasHoldem::PlayerData[result->playersN];
    result->addPlayers(0, p...);

    for (int i = 0; i < result->playersN; i++) {
        result->players[i].cash = initCash;
        result->players[i].hand = new open_card[2];
    }
    result->shuffle();

    return result;
}

template <class First>
void TexasHoldem::addPlayers(int cnt, First* first) {
    if (cnt < playersN) {
        players[cnt].p = first;
    }
}

template <class First, class... Rest>
void TexasHoldem::addPlayers(int cnt, First* first, Rest* ... rest) {
    if (cnt < playersN) {
        players[cnt].p = first;
        addPlayers(++cnt, rest...);
    }
}
