#ifndef TYPES_HPP
#define TYPES_HPP

#define NUMBER_OF_DECKS 1
#define NUMBER_OF_PILES 7

#define NUMBER_OF_SUITS 4
#define CARDS_PER_SUIT 13

static constexpr int DECK_SIZE = NUMBER_OF_SUITS * CARDS_PER_SUIT;
static constexpr int TOTAL_DECK_SIZE = DECK_SIZE * NUMBER_OF_DECKS;
static constexpr int STOCK_SIZE = TOTAL_DECK_SIZE - (NUMBER_OF_PILES * (NUMBER_OF_PILES + 1) / 2);

static constexpr int MAX_PILE_SIZE = CARDS_PER_SUIT + NUMBER_OF_PILES;

enum CARDS : int {
	JOKER, CA, C2, C3, C4, C5, C6, C7, C8, C9, CT, CJ, CQ, CK, // clubs
	SA, S2, S3, S4, S5, S6, S7, S8, S9, ST, SJ, SQ, SK, // spades
	DA, D2, D3, D4, D5, D6, D7, D8, D9, DT, DJ, DQ, DK, // diamonds
	HA, H2, H3, H4, H5, H6, H7, H8, H9, HT, HJ, HQ, HK // hearts
};

enum RANKS : int {
    ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, NO_RANK // NO_RANK for the joker
};

enum SUITS : int {
    CLUBS, SPADES, DIAMONDS, HEARTS
};

enum PILES : int {
    PILE1, PILE2, PILE3, PILE4, PILE5, PILE6, PILE7
};

struct DECK
{
    CARDS cards[TOTAL_DECK_SIZE];
    int current_card = 0;
};

struct FOUNDATION // these are the solved stacks that the user creates on double clicking
{
    CARDS stack[CARDS_PER_SUIT];
    int card_in_current_stack = 0;
    int cards = 0;
};

struct STOCK {
    CARDS stack[STOCK_SIZE];
    int cards_left = STOCK_SIZE;
    int face_card = -1; // no card removed at -1 and STOCK_SIZE
};


struct PILE
{
    CARDS pile_stack[MAX_PILE_SIZE];
    int revealed = 0;
    int card_number = 0; // number of cards in the pile
};

struct GAMESTATE {
    FOUNDATION foundations [NUMBER_OF_SUITS];
    STOCK stock;
    PILE piles[NUMBER_OF_PILES];
    int moves = 0;
    bool game_result = false;
    GAMESTATE () {
        for (int i=0; i<NUMBER_OF_PILES; i++) {
            piles[i].revealed = i; // index of the revealed card in each pile
            piles[i].card_number = i + 1; // number of cards revealed is index + 1: still don't understand but okay
        }
    }
};

/*
gives the ID of the suit
Clubs: 0
Spades: 1
Diamonds: 2
Heart: 3
*/
static constexpr int get_card_suit(CARDS card){
    return ((card - 1) / 13);
}

// gives the number on the card
static constexpr int get_card_rank (CARDS card){
    return ((card - 1) % 13);
}

#define ENABLE_INCR_OPERATIONS_ON(T)                    \
inline T& operator++(T& d) {return d = T(int(d) + 1);}  \
inline T& operator--(T& d) {return d = T(int(d) - 1);}

ENABLE_INCR_OPERATIONS_ON(CARDS)
ENABLE_INCR_OPERATIONS_ON(PILES)
// ENABLE_INCR_OPERATIONS_ON(SUITS)

#endif