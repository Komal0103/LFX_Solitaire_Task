#ifndef MOVES_HPP
#define MOVES_HPP

#include "types.hpp"

static inline void update_pile (PILE* pile) {
    if (pile->revealed == pile->card_number) {
        --pile->revealed;
    }
    if (pile->revealed < 0){
        pile->revealed = 0;
    }
    return;
}

static inline bool turn_stock (STOCK* stock) {
    if (stock->cards_left == 0) {
        return false;
    }
    while (true) {
        ++stock->face_card;
        if (stock->face_card > STOCK_SIZE) {
            stock->face_card = -1;
            return true;
        }
        if (stock->face_card == STOCK_SIZE) {
            return true;
        }
        if (stock->stack[stock->face_card] != JOKER) {
            return true;
        }
    }
    return true;
}

static inline bool stock_to_foundation (GAMESTATE* gamestate) {
    STOCK* stock = &gamestate->stock;
    bool stock_displaying_card = (stock->face_card != -1 && stock->face_card != STOCK_SIZE);
    if (stock_displaying_card) {
        CARDS stock_card = stock->stack[stock->face_card];
        int foundation_index = get_card_suit(stock_card);
        FOUNDATION* foundation = &gamestate->foundations[foundation_index];
        bool card_is_one_higher = (get_card_rank(stock_card) == foundation->cards);
        if (!card_is_one_higher) {
            return false;
        }
        /*
        if (foundation->cards == 0){
            if (get_card_rank(stock_card) != ACE) {
                return false;
            }
        }
        else {
            bool stock_card_is_one_higher = ((stock_card - 1) == (foundation->stack[foundation->cards - 1]));
            if (!stock_card_is_one_higher) {
                return false;
            }
        }
        */
        // add foundation card
        foundation->stack[foundation->cards] = stock_card;
        ++foundation->cards;

        // remove stock card
        stock->stack[stock->face_card] = JOKER;
        turn_stock(stock);
        --stock->cards_left;
        return true;
    }
    return false;
}

static inline bool pile_to_foundation (GAMESTATE* gamestate, int pile_index) {
    PILE* pile = &gamestate->piles[pile_index];
    if (pile->card_number != 0) {
        CARDS pile_card = pile->pile_stack[pile->card_number - 1];
        int foundation_index = get_card_suit(pile_card);
        FOUNDATION* foundation = &gamestate->foundations[foundation_index];

        bool card_is_one_higher = (get_card_rank(pile_card) == foundation->cards);
        if (!card_is_one_higher) {
            return false;
        }

        // add foundation card
        foundation->stack[foundation->cards] = pile_card;
        ++foundation->cards;

        // remove pile card
        --pile->card_number;
        pile->pile_stack[pile->card_number] = JOKER;
        update_pile(pile);

        return true;
    }
    return false;
}

static inline bool foundation_to_pile(PILE* pile, FOUNDATION* foundation, int foundation_index) {
    if (foundation->cards != 0) {
        CARDS foundation_card = foundation->stack[foundation->cards - 1];

        if (pile->card_number == 0 && get_card_rank(foundation_card) != KING) {
            return false;
        }
        else {
            bool is_not_same_suit = ((foundation_index >> 1) ^ (get_card_suit(pile->pile_stack[pile->card_number - 1]) >> 1));
            if (!is_not_same_suit) {
                return false;
            }
            else {
                bool card_is_one_higher = (get_card_rank(foundation_card) + 1) == (get_card_rank(pile->pile_stack[pile->card_number - 1]));
                if (!card_is_one_higher) {
                    return false;
                }
            }
        }
        // add pile card
        pile->pile_stack[pile->card_number] = foundation_card;
        ++pile->card_number;
        update_pile(pile);

        // remove foundation card
        --foundation->cards;
        foundation->stack[foundation->cards] = JOKER;
        return true;
    }
    return false;
}

static inline bool pile_to_pile(PILE* pile_from, PILE* pile_to, int card_number) {
    if (pile_from->card_number > 0) {
        int card_from_index = pile_from->card_number - card_number;
        CARDS card_from = pile_from->pile_stack[card_from_index];
        if (card_from_index < pile_from->revealed) {
            return false;
        }
        if (pile_to->card_number == 0) {
            if (get_card_rank(card_from) != KING) {
                return false;
            }
        }
        else {
            CARDS card_to = pile_to->pile_stack[pile_to->card_number - 1];
            if ((get_card_suit(card_from) >> 1) != get_card_rank(card_to)) {
                return false;
            }
            if (get_card_rank(card_from) + 1 != get_card_rank(card_to)) {
                return false;
            }
        }
        int moved_to_index = pile_to->card_number;
        for (; card_number>0; --card_number) {
            CARDS card_moved = pile_from->pile_stack[card_from_index];
            pile_to->pile_stack[moved_to_index] = card_moved;
            ++pile_to->card_number;
            ++moved_to_index;
            pile_from->pile_stack[card_from_index] = JOKER;
            --pile_from->card_number;
            ++card_from_index;
        }
        update_pile(pile_from);
        update_pile(pile_to);
        return true;
    }
    return false;
}

static inline bool stock_to_pile (PILE* pile, STOCK* stock) {
    bool stock_displaying_card = (stock->face_card != -1 && stock->face_card != STOCK_SIZE);
    if (stock_displaying_card) {
        CARDS card_from = stock->stack[stock->face_card];
        if (pile->card_number == 0){
            if (get_card_rank(card_from) != KING) {
                return false;
            }
        }
        else {
            CARDS card_to = pile->pile_stack[pile->card_number - 1];
            if ((get_card_suit(card_from) >> 1) == (get_card_suit(card_to) >>1)) {
                return false;
            }
            if ((get_card_rank(card_from) + 1) != get_card_rank(card_to)) {
                return false;
            }
        }
        int moved_from_index = stock->face_card;
        int moved_to_index = pile->card_number;

        pile->pile_stack[moved_to_index] = card_from;
        ++pile->card_number;

        stock->stack[moved_from_index] = JOKER;
        turn_stock(stock);
        --stock->cards_left;
        update_pile(pile);
        return true;
    }
    return false;
}

#endif