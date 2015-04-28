#include "deck.h"

deck::deck() {
    hand = NULL;
}

deck::~deck() {
    if (hand != NULL)
        delete[] hand;
}

void deck::print() const {
    std::cout << "Current pot: " << pot << "\n";
    std::cout << "Your cash: " << plCash << "; total bet: " << plBet << "\n";
    for (int i = 0; i < enemyN; i++) {
        std::cout << names[i] << "'s cash: " << cash[i] << "; total bet: " << bets[i] << "\n";
    }
    if (board.size() != 0) {
        std::cout << "Board cards: ";
        for (size_t i = 0; i < board.size(); i++) {
            std::cout << board[i].toString() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Your cards: " << hand[0].toString() << " " << hand[1].toString() << "\n";
}
