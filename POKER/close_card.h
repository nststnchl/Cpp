#ifndef _H_CLOSE_CARD_
#define _H_CLOSE_CARD_

#include "card.h"

class close_card : card {
public:
    close_card();
    close_card(const suit, const int);
    friend class game;
};


#endif // _H_CLOSE_CARD_
