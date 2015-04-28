#ifndef _H_UI_
#define _H_UI_

#include "player.h"
#include "open_card.h"

class Player;
class open_card;

class TextUI
{
public:
    bool noUI;
    TextUI() { noUI = false; }
    TextUI(bool ui);
    void printState(const Player& p, const deck& bs);
    void print(std::string s);
    void raise(Player *p, int to, int bet);
    void call(Player *p, int to, int bet);
    void allIn(Player *p, int total);
    void check(Player *p);
    void fold(Player *p);
    void smallBlind(Player *p, int value);
    void bigBlind(Player *p, int value);
    void showdown(Player *p, open_card *cards, int *value);
    void win(std::vector<Player*> winners);
    void gameOver(std::vector<Player*> players, std::vector<int> cash);
    int askForUnsigned(Player *p, int minBet);
};

#endif //_H_UI_
