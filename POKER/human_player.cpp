#include <iostream>

#include "human_player.h"

int HumanPlayer::bet(int minBet, deck state) {
    return UI->askForUnsigned(this, minBet);
}
