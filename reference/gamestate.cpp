#include "gamestate.hpp"
#include "deck.hpp"

#include <random>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const string ascii_suits = "CSDH";
const string ascii_ranks = "A23456789TJQK";

static inline void print_stock_card (STOCK* stock) {
    if (stock->face_card == -1 || stock->face_card == STOCK_SIZE) {
        cout<<"NIL ";
        return;
    }
    if (stock->stack[stock->face_card] != JOKER) {
        cout<<ascii_suits[get_card_suit(stock->stack[stock->face_card])];
        cout<<ascii_ranks[get_card_rank(stock->stack[stock->face_card])];
    }
    return;
}

static inline void print_foundation_card (FOUNDATION* foundation) {
    if (foundation->cards == 0) {
        cout<<"NIL ";
        return;
    }
    cout<<ascii_suits[get_card_suit(foundation->stack[foundation->cards - 1])];
    cout<<ascii_ranks[get_card_rank(foundation->stack[foundation->cards - 1])]<<" ";
    return;
}

static inline void print_card (CARDS card) {
    if (card != JOKER) {
        cout<<ascii_suits[get_card_suit(card)];
        cout<<ascii_ranks[get_card_rank(card)];
    }
    return;
}

void print_pile(PILE* pile, bool hidden) {
    for (int i=0; i<pile->card_number; ++i) {
        if (i>=pile->revealed || !hidden) {
            print_card(pile->pile_stack[i]);
            cout<<" ";
        }
        else {
            cout<<"**";
        }
        cout<<" ";
    }
    cout<<endl;
}
void print_gamestate(GAMESTATE* gamestate, bool hidden) {
    cout<<endl;
    cout<<"Current stock card: ";
    print_stock_card(&gamestate->stock);

    cout<<endl;
    cout<<"Foundations: ";
    print_foundation_card(&gamestate->foundations[0]);
    print_foundation_card(&gamestate->foundations[1]);
    print_foundation_card(&gamestate->foundations[2]);
    print_foundation_card(&gamestate->foundations[3]);

    cout << "\n              C  S  D  H ";
    cout << "\nPILES:";
    cout << "                 MOVES: " << gamestate->moves << endl;

    for (PILES pile = PILE7; pile >= 0; --pile) {
        // Each card
        cout << endl << pile + 1 << ':';
        print_pile(&gamestate->piles[pile], hidden);
    }
    cout << endl;
}

GAMESTATE start_game() {
    GAMESTATE gamestate;
    DECK deck;
    fill_deck(&deck);
    shuffle_deck(&deck);

    // 7 piles
    for (PILES pile = PILE1; pile < NUMBER_OF_PILES;) {
        // Each card
        CARDS* start = (deck.cards + deck.current_card);
        ++pile;
        deck.current_card += (pile);
        CARDS* end = (deck.cards + deck.current_card);
        copy(start, end, gamestate.piles[pile - 1].pile_stack);
    }

    // rest into stock
    CARDS* start = (deck.cards + deck.current_card);
    deck.current_card += STOCK_SIZE;
    CARDS* end = (deck.cards + deck.current_card);
    copy(start, end, gamestate.stock.stack);

    return gamestate;
}