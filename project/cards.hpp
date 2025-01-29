#include <string>

using namespace std;

// macros for defining the number of cards

class Cards {
    enum ALL_CARDS : int {
        JOKER, CA, C2, C3, C4, C5, C6, C7, C8, C9, CT, CJ, CQ, CK, // clubs
	SA, S2, S3, S4, S5, S6, S7, S8, S9, ST, SJ, SQ, SK, // spades
	DA, D2, D3, D4, D5, D6, D7, D8, D9, DT, DJ, DQ, DK, // diamonds
	HA, H2, H3, H4, H5, H6, H7, H8, H9, HT, HJ, HQ, HK // hearts
    };

    enum SUITS : int {
        HEARTS, DIAMONDS, CLUBS, SPADES
        // 00   01          10      11
    };

    enum CARD_RANKS : int {
        ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };

    public:
        int get_card_suit(string* card);
        int get_card_rank (string* card);
        int get_card_color (string card); // 0 for red, 1 for blue
};