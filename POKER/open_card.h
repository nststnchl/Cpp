#ifndef _H_OPEN_CARD_
#define _H_OPEN_CARD_

#include "card.h"


class open_card: card {
public:
    open_card();
    open_card(const suit, const int);
    int getRank() const;
    suit getSuit() const;
    bool operator ==(open_card const& another);
    std::string toString() const;
};

#endif // _H_OPEN_CARD_
