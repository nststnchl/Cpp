#ifndef _H_HUMAN_PLAYER_
#define _H_HUMAN_PLAYER_

#include "player.h"
#include "UI.h"

class HumanPlayer: public Player {
private:
    TextUI* UI;
public:
    HumanPlayer() {};
    HumanPlayer(std::string s, TextUI* ui): Player(s) { UI = ui; }
    ~HumanPlayer() {};
    int bet(int minBet, deck state);
    bool getUI();
};

#endif //_H_HUMAN_PLAYER_
