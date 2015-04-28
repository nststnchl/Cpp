#ifndef _H_CARD_
#define _H_CARD_

#include <iostream>

enum suit { clubs, diamonds, hearts, spades };

class card
{
protected:
    suit s;
    int rank;

public:
    card() {};
};

#endif // _H_CARD_
