#include "open_card.h"

open_card::open_card()
{
    s = suit::clubs;
    rank = 0;
}

open_card::open_card(const suit s, const int rank)
{
    this -> s = s;
    this -> rank = rank;
}

int open_card::getRank() const
{
    return rank;
}

suit open_card::getSuit() const
{
    return s;
}

bool open_card::operator ==(open_card const& other)
{
    if (rank != other.getRank())
        return false;

    if (s != other.getSuit())
        return false;

    return true;
}

std::string open_card::toString() const
{
    std::string connect = " of ";
    std::string first[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    std::string second[] = {"clubs", "diamonds", "hearts", "spades"};
    std::string result = first[rank - 2] + connect + second[(int) s];
    return result;
}
