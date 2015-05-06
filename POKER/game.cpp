#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <string.h>
#include <cmath>

#include "close_card.h"
#include "open_card.h"
#include "game.h"
#include "deck.h"
#include "UI.h"

namespace {
    int myUpperBound(std::vector<int> inGame, int x) {
        if (std::count(inGame.begin(), inGame.end(), x))
            return x;

        auto result = std::upper_bound(inGame.begin(), inGame.end(), x);
        if (result == inGame.end())
            return inGame[0];
        return *result;
    }
    bool highestRankFirst(const open_card &a, const open_card &b) {
        return a.getRank() > b.getRank();
    }

    bool bySuit(const open_card &a, const open_card &b) {
        if ((int) a.getSuit() == (int) b.getSuit())
            return a.getRank() < b.getRank();
        return (int) a.getSuit() < (int) b.getSuit();
    }
}

game::game() {}

int* game::evaluate(open_card *cards) {
    int *result = new int[7];
    for (int i = 0; i < 7; i++) {
        result[i] = 0;
    }

    std::sort(cards, cards + 5, bySuit);
    if (cards[0].getSuit() == cards[4].getSuit()) {
        result[0] = 5;
        result[1] = (int) cards[4].getRank();;
        result[2] = (int) cards[4].getRank();
        result[3] = (int) cards[3].getRank();
        result[4] = (int) cards[2].getRank();
        result[5] = (int) cards[1].getRank();
        result[6] = (int) cards[0].getRank();
    }

    std::sort(cards, cards + 5, highestRankFirst);
    int diff[4], pos = 0;
    for (int i = 0; i < 4; i++) {
        if (cards[i].getRank() - cards[i + 1].getRank() > 1)
            pos = i + 1;
        diff[i] = cards[i].getRank() - cards[i + 1].getRank();
    }

    bool straight = true;
    for (int i = pos; i < pos + 4; i++) {
        if ((i + 1) % 5 == 0) {
            if ((cards[4].getRank() != 2 || cards[0].getRank() != 14) && pos != 0)
                straight = false;
        }
        else if (cards[i % 5].getRank() - cards[(i + 1) % 5].getRank() != 1)
            straight = false;
    }

    if (straight) {
        result[1] = (int) cards[std::max(pos - 1, 0)].getRank();
        if (result[0] == 5) {
            if (cards[0].getRank() == 14 && cards[4].getRank() == 10)
                result[0] = 9;
            else
                result[0] = 8;
        }
        else
            result[0] = 4;
    }

    int code = 0;
    for (int i = 0; i < 4; i++) {
        code |= (1 << i) * (diff[3 - i] != 0);
    }

    if (code == 1 && result[0] < 7) {
        result[0] = 7;
        result[1] = (int) cards[0].getRank();
        result[2] = (int) cards[4].getRank();
    }
    else if (code == 8 && result[0] < 7) {
        result[0] = 7;
        result[1] = (int) cards[1].getRank();
        result[2] = (int) cards[0].getRank();
    }
    else if (code == 2 && result[0] < 6) {
        result[0] = 6;
        result[1] = (int) cards[0].getRank() * 14 + cards[3].getRank();
    }
    else if (code == 4 && result[0] < 6) {
        result[0] = 6;
        result[1] = (int) cards[3].getRank() * 14 + cards[0].getRank();
    }
    else if (code == 3 && result[0] < 3) {
        result[0] = 3;
        result[1] = (int) cards[0].getRank();
        result[2] = (int) cards[3].getRank();
        result[3] = (int) cards[4].getRank();
    }
    else if (code == 9 && result[0] < 3) {
        result[0] = 3;
        result[1] = (int) cards[1].getRank();
        result[2] = (int) cards[0].getRank();
        result[3] = (int) cards[4].getRank();
    }
    else if (code == 12 && result[0] < 3) {
        result[0] = 3;
        result[1] = (int) cards[2].getRank();
        result[2] = (int) cards[0].getRank();
        result[3] = (int) cards[1].getRank();
    }
    else if (code == 5 && result[0] < 2) {
        result[0] = 2;
        result[1] = (int) std::max(cards[0].getRank(), cards[2].getRank()) * 14 +
                std::min(cards[0].getRank(), cards[2].getRank());
        result[2] = (int) cards[4].getRank();
    }
    else if (code == 6 && result[0] < 2) {
        result[0] = 2;
        result[1] = (int) std::max(cards[0].getRank(), cards[3].getRank()) * 14 +
                std::min(cards[0].getRank(), cards[3].getRank());
        result[2] = (int) cards[2].getRank();
    }
    else if (code == 10 && result[0] < 2) {
        result[0] = 2;
        result[1] = (int) std::max(cards[1].getRank(), cards[3].getRank()) * 14 +
                std::min(cards[1].getRank(), cards[3].getRank());
        result[2] = (int) cards[0].getRank();
    }
    else if (code == 7 && result[0] < 1) {
        result[0] = 1;
        result[1] = (int) cards[0].getRank();
        result[2] = (int) cards[2].getRank();
        result[3] = (int) cards[3].getRank();
        result[4] = (int) cards[4].getRank();
    }
    else if (code == 11 && result[0] < 1) {
        result[0] = 1;
        result[1] = (int) cards[1].getRank();
        result[2] = (int) cards[0].getRank();
        result[3] = (int) cards[3].getRank();
        result[4] = (int) cards[4].getRank();
    }
    else if (code == 13 && result[0] < 1) {
        result[0] = 1;
        result[1] = (int) cards[2].getRank();
        result[2] = (int) cards[0].getRank();
        result[3] = (int) cards[1].getRank();
        result[4] = (int) cards[4].getRank();
    }
    else if (code == 14 && result[0] < 1) {
        result[0] = 1;
        result[1] = (int) cards[3].getRank();
        result[2] = (int) cards[0].getRank();
        result[3] = (int) cards[1].getRank();
        result[4] = (int) cards[2].getRank();
    }
    else if (result[0] == 0) {
        result[1] = 0;
        for (int i = 0; i < 5; i++)
            result[1 + i] = (int) cards[i].getRank();
    }

    return result;
}

game::~game() {
    delete[] players;
    delete UI;
}

game::PlayerData::~PlayerData() {
    delete[] hand;
    delete p;
}

namespace {
    bool nextCombination(size_t* item, size_t n, size_t N) {
        for (size_t i = 1; i <= n; ++i) {
            if (item[n-i] < N-i) {
                ++item[n-i];
                for (size_t j = n-i+1; j < n; ++j) {
                    item[j] = item[j-1] + 1;
                }
                return true;
            }
        }
        return false;
    }

    int int7cmp (int* a, int* b) {
        for (int i = 0; i < 7; i++) {
            if (a[i] != b[i]) {
                return - (a[i] < b[i]) + (a[i] > b[i]);
            }
        }
        return 0;
    }
}

std::pair <open_card*, int*> game::highestComb(open_card* source) {
    size_t cardIndex[5], n = 7, k = 5;
    for (size_t i = 0; i < k; i++) {
        cardIndex[i] = i;
    }
    int *currValue, *maxValue = new int[7];
    memset(maxValue, 0, sizeof(int) * 7);
    open_card *curr = new open_card[k], *maxcard = new open_card[k];
    do {
        for (size_t i = 0; i < k; i++) {
            curr[i] = source[cardIndex[i]];
        }
        currValue = evaluate(curr);
        if (int7cmp(currValue, maxValue) == 1) {
            memcpy(maxValue, currValue, sizeof(int) * 7);
            memcpy(maxcard, curr, sizeof(open_card) * k);
        }
        delete[] currValue;
    } while (nextCombination(cardIndex, k, n));
    delete[] curr;

    return std::make_pair(maxcard, maxValue);
}

std::vector<int> game::refresh() {
    std::vector<int> result;
    for (int i = 0; i < playersN; i++) {
        if (players[i].cash != 0)
            result.push_back((int const &) i);
    }
    return result;
}

void game::doRound() {
    UI->print("New round\n");
    board.clear();
    int small = myUpperBound(inGame, (dealer + 1) % playersN),
            big = myUpperBound(inGame, (small + 1) % playersN);
    int m1 = std::min(smallBlind, players[small].cash);
    players[small].cash -= std::min(smallBlind, players[small].cash);
    players[small].currBet = std::min(smallBlind, players[small].cash);
    UI->smallBlind(players[small].p, std::min(smallBlind, players[big].cash));
    int m2 = std::min(smallBlind * 2, players[big].cash);
    players[big].cash -= std::min(smallBlind * 2, players[big].cash);
    players[big].currBet = std::min(smallBlind * 2, players[big].cash);
    UI->bigBlind(players[big].p, std::min(smallBlind * 2, players[big].cash));
    pot = m1 + m2;
    //pot = std::min(smallBlind, players[small].cash) + std::min(smallBlind * 2, players[big].cash);

    int underTheGun = big = myUpperBound(inGame, (big + 1) % playersN);
    doBets(underTheGun);
    for (int i = 0; i < 3; i++)
        openNext();
    if (inGameWithCash() > 1)
        doBets(underTheGun);
    openNext();
    if (inGameWithCash() > 1)
        doBets(underTheGun);
    openNext();
    if (inGameWithCash() > 1)
        doBets(underTheGun);
    std::vector<int> winners = showdown();
    assert(winners.size() > 0);
    std::vector<Player*> winnersPointers;
    for (size_t i = 0; i < winners.size(); i++) {
        players[winners[i]].cash += pot / winners.size();
        winnersPointers.push_back(players[winners[i]].p);
    }
    UI->win(winnersPointers);
}

void game::doBets(int underTheGun) {
    int last = underTheGun, curr = last, value = 0, currBet = 0;
    for (size_t i = 0; i < inGame.size(); i++) {
        currBet = std::max(currBet, players[inGame[i]].currBet);
    }

    do {
        if (players[curr].cash != 0) {
            if (!((*players[curr].p).getUI()))
                UI->printState(*players[curr].p, getState(curr, inGame));
            for (int i = 0; i < 3; i++) {
                bool wrongInput = false;
                try {
                    value = players[curr].p->bet(currBet - players[curr].currBet, getState(curr, inGame));
                }
                catch (...){
                    wrongInput = true;

                }
                if (((players[curr].cash >= value && value + players[curr].currBet >= currBet) || value == 0 ||
                     value == players[curr].cash) && !wrongInput)
                    break;
                if (i == 2) {
                    value = 0;
                    if (!((*players[curr].p).getUI()))
                        UI->print("wrong value, check/fold by default\n");
                    break;
                }
                else
                    if (!((*players[curr].p).getUI()))
                        UI->print("wrong value, try again (" + std::to_string(2 - i) + ")\n");
            }
            if (value > 0) {
                if (value + players[curr].currBet > currBet) {
                    last = curr;
                    currBet = value + players[curr].currBet;
                    if (value == players[curr].cash)
                        UI->allIn(players[curr].p, currBet);
                    else
                        UI->raise(players[curr].p, currBet, value);
                }
                else {
                    if (value == players[curr].cash)
                        UI->allIn(players[curr].p, players[curr].currBet + value);
                    else
                        UI->call(players[curr].p, currBet, value);
                }
                players[curr].cash -= value;
                players[curr].currBet += value;
                pot += value;
            }
            else {
                if (currBet - players[curr].currBet == 0) {
                    UI->check(players[curr].p);
                }
                else {
                    UI->fold(players[curr].p);
                    assert(std::find(inGame.begin(), inGame.end(), curr) != inGame.end());
                    inGame.erase(std::find(inGame.begin(), inGame.end(), curr));
                    if (inGame.size() == 1)
                        return;
                }
            }
        }
        curr = myUpperBound(inGame, (curr + 1) % playersN);
    } while (curr != last);
}

std::vector<int> game::showdown() {
    std::vector<int> winners;
    int *maxValue = new int[7];
    memset(maxValue, 0, sizeof(int) * 7);
    open_card currcards[7];
    assert(board.size() == 5);
    for (int j = 0; j < 5; j++) {
        currcards[j] = board[j];
    }
    for (size_t i = 0; i < inGame.size(); i++) {
        currcards[5] = players[inGame[i]].hand[0];
        currcards[6] = players[inGame[i]].hand[1];
        std::pair<open_card*, int*> curr = highestComb(currcards);
        switch(int7cmp(curr.second, maxValue)) {
            case 1:
                winners.clear();
                winners.push_back(inGame[i]);
                memcpy(maxValue, curr.second, 7 * sizeof(int));
                break;
            case 0:
                winners.push_back(inGame[i]);
                break;
            default:
                break;
        }

        if (inGame.size() > 1)
            UI->showdown(players[inGame[i]].p, curr.first, curr.second);
        delete[] curr.first;
        delete[] curr.second;
    }
    delete[] maxValue;

    return winners;
}

void game::shuffle() {
    UI->print("Shuffling cards...\n\n");

    const int N = 52;
    std::pair<suit, int> deckTmp[N];
    for (int i = 2; i <= 14; i++) {
        for (int j = suit::clubs; j <= suit::spades; j++) {
            deckTmp[(i - 2) * 4 + j] = std::make_pair((suit) j, i);
        }
    }

    std::srand((int) (time(0)));
    std::random_shuffle(deckTmp, deckTmp + N);
    for (int i = 0; i < playersN; i++) {
        players[i].hand[0] = open_card(deckTmp[i * 2].first, deckTmp[i * 2].second);
        players[i].hand[1] = open_card(deckTmp[i * 2 + 1].first, deckTmp[i * 2 + 1].second);
    }

    for (int i = playersN * 2; i < playersN * 2 + 5; i++) {
        cl_deck.push_back(close_card(deckTmp[i * 2].first, deckTmp[i * 2].second));
    }
}

void game::openNext() {
    close_card chosen = cl_deck.back();
    cl_deck.erase(--cl_deck.end());
    board.push_back(open_card(chosen.s, chosen.rank));
}    

deck game::getState(int player, std::vector <int> inGame) {
    int isActive = (int) std::count(inGame.begin(), inGame.end(), player);

    deck bs;
    bs.enemyN = (int) (inGame.size() - isActive);
    bs.pot = pot;
    bs.smallBlind = smallBlind;
    bs.plBet = players[player].currBet;
    bs.plCash = players[player].cash;
    for (size_t i = 0; i < inGame.size(); i++) {
        if (inGame[i] != player) {
            bs.bets.push_back(players[inGame[i]].currBet);
            bs.cash.push_back(players[inGame[i]].cash);
            bs.names.push_back(players[inGame[i]].p->getName());
        }
    }
    bs.hand = new open_card[2];
    memcpy(bs.hand, players[player].hand, sizeof(open_card) * 2);
    bs.board = board;

    return bs;
}

size_t game::inGameWithCash() {
    size_t cnt = 0;
    for (size_t i = 0; i < inGame.size(); i++) {
        cnt += (players[inGame[i]].cash != 0);
    }
    return cnt;
}

void game::run() {
    inGame = refresh();
    dealer = 0;
    pot = 0;

    while (inGame.size() > 1) {
        dealer = myUpperBound(inGame, (dealer + 1) % playersN);
        shuffle();

        doRound();
        pot = 0;
        inGame = refresh();
    }

    std::vector<Player*> pl;
    std::vector<int> c;
    for (int i = 0; i < playersN; i++) {
        pl.push_back(players[i].p);
        c.push_back(players[i].cash);
    }
    UI->gameOver(pl, c);
}
