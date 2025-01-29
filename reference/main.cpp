#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <cstdio>
#include <map>

#include "types.hpp"
#include "gamestate.hpp"
#include "moves.hpp"
#include "init.hpp"
#include "io.hpp"

using namespace std;

enum COMMANDS {
    unrecognized_command, new_game, display_screen, help, quit, move_command, search_command
};

static map<string, COMMANDS> MAP_COMMANDS = {
    {"newgame", new_game}, {"d", display_screen}, {"help", help}, {"quit", quit}, {"move", move_command}, {"search", search_command}
};

static map<char, int> char_suits = {
    {'C', CLUBS}, {'S', SPADES}, {'D', DIAMONDS}, {'H', HEARTS}
};

static void Parse_help(vector<string> tokens) {
	if (tokens.size() == 1) {
		cout << "\nCommands:\n\"help\":      Provides help information for commands.\n\"newgame\":   Starts a new Klondike game.\n\"d\":         Prints current game state.\n\"quit\":      Closes game client.\n\"move\":      Move card location.\n\n";
		return;
	}
	switch (MAP_COMMANDS[tokens[1]])
	{
	case (quit):
	{
		cout << "Closes game client.\n\nquit\n\n";
		break;
	}
	case (help):
	{
		cout << "Provides help information for commands.\n\nhelp command\n\n	command - displays help information on that command.\n\n";
		break;
	}
	case (display_screen):
	{
		cout << "Prints current game state.\n\nd\n\n";
		break;
	}
	case (new_game):
	{
		cout << "Starts a new Klondike game.\n\nnewgame\n\n";
		break;
	}
	case (move_command):
	{
		cout << "Move card location.\n\nmove operation [source] [destination]\n\n";
		cout << "	operation - type of move to be performed\n";
		cout << "		 T	move the stock card to the waste pile or turning over the stock.\n\n";
		cout << "		pp	move a partial pile or card from one pile to another.\n";
		cout << "			-[source]	location and number of partial pile to move.\n					(Ex: 23, move 3 cards from the top of pile 2)\n";
		cout << "			-[destination]	location of pile to move to.\n\n";
		cout << "		sp	move a card from the stock to a pile, only destination is needed to be specified.\n";
		cout << "			-[destination]	location of pile to move to.\n\n";
		cout << "		sf	move a card from the stock to a foundation.\n\n";
		cout << "		pf	move a card from a pile to a foundation.\n";
		cout << "			-[source]	location of pile to move the card from. (Ex: 2, move a card from the top of pile 2)\n\n";
		cout << "		fp	move a card from a foundation to a pile.\n";
		cout << "			-[destination]	location of pile to move to.\n\n";
		cout << "		hint	have the computer play a move for you.\n\n";
		break;
	}
	case (unrecognized_command):
	{
		cout << "Unknown command\n";
		break;
	}
	}
	return;
}

void Parse_move(vector<string> tokens, GAMESTATE* gamestate) {
	if (tokens.size() == 1) {
		cout << "Invalid command size!\n";
	}
	else if (tokens.at(1) == "T") {
		try {
			if (!turn_stock(&gamestate->stock)) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "pp") {
		try {
			int input_index = stoi(tokens.at(2));
			int pile_from = (input_index / 10) - 1;
			int card_index = input_index % 10;
			int pile_to = stoi(tokens.at(3)) - 1;
			if (!pile_to_pile(&gamestate->piles[pile_from], &gamestate->piles[pile_to], card_index)) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "sp") {
		try {
			int pile_to = stoi(tokens.at(2)) - 1;
			if (!stock_to_pile(&gamestate->piles[pile_to], &gamestate->stock)) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "sf") {
		try {
			if (!stock_to_foundation(gamestate)) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "pf") {
		try {
			int pile = stoi(tokens.at(2)) - 1;
			if (!pile_to_foundation(gamestate, pile)) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "fp") {
		try {
			int pile = stoi(tokens.at(3)) - 1;
			if (!foundation_to_pile(&gamestate->piles[pile], &gamestate->foundations[pile], char_suits[tokens.at(2)[0]])) {
				cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}

		catch (...) {
			cout << "Formatting error!\n";
		}
	}
	/*
	else if (tokens.at(1) == "hint") {
		if (Move_hint(gamestate)) {
			++gamestate->moves;
		}

		else {
			cout << "No moves found.\n";
		}
	}*/
	else {
		cout << "Invalid Command!\n";
	}

	return;
}

int main(){
    init_all();
    cout<<"Type \"help\" for command line options"<<endl;

    GAMESTATE gamestate;
    bool game_started = false;

    while (true) {
        string input;

        if (!getline(cin, input)) {
            break;
        }

        if (!input.length()) {
            continue;
        }

        vector<string> tokens= split_command(input);

        switch (MAP_COMMANDS[tokens[0]])
        {
            case (quit):
                return 0;
            case (help):
            Parse_help(tokens);
                break;
            case (display_screen):
            {
                if (game_started)
                    print_gamestate(&gamestate);
                else
                    cout<<"No game available"<<endl;
                break;
            }
            case (new_game):
            {
                start_game();
                game_started = true;
                break;
            }
            case (move_command):
            {
                if (game_started) {
                    Parse_move (tokens, &gamestate);
                }
                else {
                    cout<<"No game available"<<endl;
                }
                break;
            }
            case (search_command):
            // code to be inserted
                break;
            case (unrecognized_command):
            {
                cout<<"Unknown command"<<endl;
                break;
            }        
            default:
                break;
        }
    }

    return 0;
}