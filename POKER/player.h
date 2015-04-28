#ifndef _H_PLAYER_
#define _H_PLAYER_

#include <string>

#include "game.h"
#include "deck.h"

class deck;

class Player {
private:
    std::string name;
public:
    Player() {};
    Player(std::string n) { name = n; }
    std::string getName() const { return name; }
    virtual ~Player() {};
    virtual int bet(int minBet, deck state) = 0;
};

#endif //_H_PLAYER_
