#include "deck.hpp"

#include <random>
#include <algorithm>

using namespace std;

void fill_deck (DECK* deck) {
    int index = 0;
    for (int current_deck=0; current_deck<NUMBER_OF_DECKS; ++current_deck) {
        // for each of 52 cards, do the following
        for (CARDS card= CA; card<=HK; ++card) {
            deck->cards[index] = card;
            ++index;
        }
    }
}

void shuffle_deck (DECK* deck) {
    random_shuffle(deck->cards, deck->cards + TOTAL_DECK_SIZE);
}