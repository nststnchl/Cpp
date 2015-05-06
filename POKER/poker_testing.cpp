#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "gtest/gtest.h"
#include "game.h"
#include "start_game.cpp"
#include "human_player.h"
#include "UI.h"
#include "player.h"

namespace {
    const int N = 1000;
    const char *testFile = "test.txt",
               *handFile = "hand.txt";

    std::pair<size_t, open_card*> readCards(const char* path) {
        std::ifstream fin(path);
        int m, rank, s;
        fin >> m;
        open_card* out = new open_card[m];
        for (int i = 0; i < m; i++) {
            fin >> rank >> s;
            out[i] = open_card((suit)s, rank);
        }

        return std::make_pair(m, out);
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

TEST(correctness, constructor) {
    TextUI* ui = new TextUI(true);
    game* my_game = createGame((int)2, (int)100, (int) 10, ui,
            new HumanPlayer("First player", ui), new HumanPlayer("Second player", ui));
    delete my_game;
}

TEST(correctness, shuffleTest) {
    TextUI* ui = new TextUI(true);
    game* my_game = createGame((int)2, (int)100, (int) 10, ui,
            new HumanPlayer("First player", ui), new HumanPlayer("Second player", ui));
    open_card cards[9];
    for (int i = 0; i < N; i++) {
        my_game->shuffle();
        for (int j = 0; j < 5; j++) {
            my_game->openNext();
            cards[j] = my_game->board.back();
        }
        cards[5] = my_game->players[0].hand[0];
        cards[6] = my_game->players[0].hand[1];
        cards[7] = my_game->players[1].hand[0];
        cards[8] = my_game->players[1].hand[1];

        for (int j = 0; j < 9; j++) {
            EXPECT_TRUE(cards[j].getRank() >= 2);
            EXPECT_TRUE(cards[j].getRank() <= 14);
            EXPECT_TRUE((int)cards[j].getSuit() <= 4);
            EXPECT_EQ(1, std::count(cards, cards + 9, cards[j]));
        }
    }
    delete my_game;
}

TEST(correctness, evaluateCombination) {
    TextUI* ui = new TextUI(true);
    game* my_game = createGame((int)2, (int)100, (int) 10, ui,
            new HumanPlayer("First player", ui), new HumanPlayer("Second player", ui));
    std::pair<size_t, open_card*> out = readCards(testFile);
    open_card *testCards = out.second;

    srand (time(NULL));
    for (size_t i = 0; i < out.first / 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::swap(testCards[5 * i + j], testCards[5 * i + rand() % 5]);
        }
    }

    int *valueI, *valueJ;
    for (size_t i = 0; i < out.first / 5; i++) {
        valueI = my_game->evaluate(&testCards[5 * i]);
        for (size_t j = 0; j < out.first / 5; j++) {
            valueJ = my_game->evaluate(&testCards[5 * j]);
            if (i != j) {
                EXPECT_EQ(i < j ? -1 : 1, int7cmp(valueI, valueJ));
                if ((i < j ? -1 : 1) != int7cmp(valueI, valueJ)) {
                    std::cout << i << " " << j << "\n";
                }
            }
            else {
                EXPECT_EQ(0, int7cmp(valueI, valueJ));
            }
            delete[] valueJ;
        }
        delete[] valueI;
    }

    delete[] testCards;
    delete my_game;
}

TEST(correctness, pickCombination) {
    TextUI* ui = new TextUI(true);
    game* my_game = createGame((int)2, (int)100, (int) 10, ui,
            new HumanPlayer("First player", ui), new HumanPlayer("Second player", ui));
    std::pair<size_t, open_card*> out = readCards(handFile);
    open_card *testCards = out.second;
    open_card *shuffledCards = new open_card[out.first];
    memcpy(shuffledCards, out.second, out.first * sizeof(open_card));

    srand (time(NULL));
    for (size_t i = 0; i < out.first / 7; i++) {
        for (int j = 0; j < 7; j++) {
            std::swap(shuffledCards[7 * i + j], shuffledCards[7 * i + rand() % 7]);
        }
    }

    for (int i = 0; i < (int) out.first / 7; i++) {
        std::pair<open_card*, int*> result = my_game->highestComb(&shuffledCards[i * 7]);
        for (int j = 0; j < 5; j++) {
            if (std::count(testCards + i * 7, testCards + i * 7 + 5, result.first[j]) != 1) {
                int x = 0;
                x++;
            }
            EXPECT_EQ(1, std::count(testCards + i * 7, testCards + i * 7 + 5, result.first[j]));
        }
        delete[] result.first;
        delete[] result.second;
    }

    delete[] testCards;
    delete[] shuffledCards;
    delete my_game;
}
