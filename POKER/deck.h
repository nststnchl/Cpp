#ifndef _H_DECK_
#define _H_DECK_

#include "open_card.h"
#include <vector>

class open_card;

class deck {
public:
    int enemyN, pot, smallBlind, plCash, plBet;
    open_card *hand;
    std::vector <open_card> board;
    std::vector <std::string> names;
    std::vector <int> cash, bets;

    deck();
    ~deck();
    
    void print() const;
};

#endif //_H_DECK_
