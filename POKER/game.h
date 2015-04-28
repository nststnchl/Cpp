#ifndef _H_GAME_
#define _H_GAME_

#include <vector>
#include "gtest/gtest.h"
#include "open_card.h"
#include "close_card.h"
#include "player.h"
#include "deck.h"
#include "UI.h"

class open_card;
class close_card;
class Player;
class deck;
class TextUI;

class TexasHoldem {
private:
    struct PlayerData {
        int cash;
        open_card* hand;
        int currBet;
        Player* p;

        ~PlayerData();
    } *players;
    int playersN, pot, smallBlind, dealer;

    int* evaluate(open_card* cards);
    std::pair <open_card*, int*> highestComb(open_card*);
    std::vector<int> showdown();
    void doBets(int underTheGun);
    void doRound();
    void shuffle();
    std::vector<int> refresh();
    void openNext();
    size_t inGameWithCash();
    deck getState(int player, std::vector<int> inGame);
    std::vector <open_card> board;
    std::vector <close_card> cl_deck;

    std::vector<int> inGame;

    template <class First>
    void addPlayers(int cnt, First* first);
    template <class First, class... Rest>
    void addPlayers(int cnt, First* first, Rest* ... rest);

    TexasHoldem();
    template <class ... Players>
    friend TexasHoldem* createGame(int n, int initCash, int smallBlind,
                                   TextUI* ui, Players* ... p);

    TextUI* UI;

    FRIEND_TEST(correctness, evaluateCombination);
    FRIEND_TEST(correctness, pickCombination);
    FRIEND_TEST(correctness, shuffleTest);
public:
    ~TexasHoldem();
    void run();
};

#endif //_H_GAME_
