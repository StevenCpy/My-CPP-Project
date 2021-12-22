#include "card.h"
#include "deck.h"
#include "player.h"
#include "table.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

// converts rank of card from char to int
int rankToInt(char rank) {
    if (rank == 'A') return 1;
    if (rank == 'T') return 10;
    if (rank == 'J') return 11;
    if (rank == 'Q') return 12;
    if (rank == 'K') return 13;
    return rank - '0';
}

int main(int argc, char * argv[]) {
    std::vector<bool> isPlayerHuman;
    char in;

    // use a time-based seed for the default seed value
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // if seed is provided as command-line argument to the executable
    if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
	}

    // sets the table for the player types, by determining whether each is human or a computer
    for (int i = 0; i < 4; ++i) {
        std::cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << std::endl;
        std::cin >> in;
        if (in == 'h') {
            isPlayerHuman.push_back(true);
        } else {
            isPlayerHuman.push_back(false);
        }
    }

    // constructs the table
    Table table{isPlayerHuman[0], isPlayerHuman[1], isPlayerHuman[2], isPlayerHuman[3], seed};

    bool gameOver = false; // true if any player has score >= 80

    bool strat = false; // by default false means computer players play first legal move or discards first card

    while (!gameOver) {
        table.deckShuffle(); // shuffles the deck
        table.deal(); // deals the cards to each player

        int playerTurn = table.startingPlayer(); // determines starting player

        bool firstPlay = true;

        std::cout << "A new round begins.  It's Player" << playerTurn + 1 << "'s turn to play." << std::endl;
        while (!table.emptyHand(playerTurn)) { // while no player has an empty hand
            std::cout << "Cards on the table:" << std::endl;
            table.printTableCards();
            std::cout << "Your hand:";
            table.printHand(playerTurn);
            std::cout << std::endl;
            std::cout << "Legal plays:";
            if (firstPlay) {
                std::cout << " 7S";
            } else {
                table.printLegal(playerTurn);
            }
            std::cout << std::endl;

            if (table.isPlayerHuman(playerTurn)) { // player is a human, give prompts
                bool valid = false;

                while (!valid) {
                    std::string command;

                    std::cin >> command;
                    if (command == "play") { // play <card> to play the chosen card
                                             // input by human player eg. play 2C
                                             // card must be in player's hand and be a legal move
                        char rank;
                        char suit;
                        std::cin >> rank;
                        int irank = rankToInt(rank);
                        std::cin >> suit;
                        if (!table.cardInHand(playerTurn, irank, suit)) { // card not in player's hand
                            std::cout << "You don't have this card in your hand." << std::endl;
                        } else if (firstPlay) { // first player has to play the 7 of spades
                            if (irank == 7 && suit == 'S') {
                                std::cout << "Player" << playerTurn + 1 << " plays 7S." << std::endl;
                                valid = true;
                                firstPlay = false;
                                table.play(playerTurn, irank, suit);
                            } else {
                                std::cout << "You have to play the 7 of spades first." << std::endl;
                            }
                        } else if (table.isLegal(irank, suit)) { // card is a legal move
                            std::cout << "Player" << playerTurn + 1 << " plays " << table.intToRank(irank) << suit << "." << std::endl;
                            valid = true;
                            table.play(playerTurn, irank, suit);
                        } else { // card is not a legal move
                            std::cout << "This is not a legal play." << std::endl;
                        }
                    } else if (command == "discard") { // discard <card> to discard the chosen card
                                                       // input by human player eg. discard 2C
                                                       // card must be in player's hand and player must have no legal moves
                        char rank;
                        char suit;
                        std::cin >> rank;
                        int irank = rankToInt(rank);
                        std::cin >> suit;
                        if (!table.cardInHand(playerTurn, irank, suit)) { // not in player's hand
                            std::cout << "You don't have this card in your hand." << std::endl;
                        } else if (table.hasLegalMoves(playerTurn)) { // player has legal moves
                            std::cout << "You have a legal play.  You may not discard." << std::endl;
                        } else {
                            std::cout << "Player" << playerTurn + 1 << " discards " << table.intToRank(irank) << suit << "." << std::endl;
                            valid = true;
                            table.discard(playerTurn, irank, suit);
                        }
                    } else if (command == "deck") { // prints the deck
                                                    // input by human player: deck
                        table.printDeck();
                    } else if (command == "quit") { // terminates the program
                                                    // input by human player: quit
                        std::cout << "The program has been terminated." << std::endl;
                        return 1;
                    } else if (command == "ragequit") { // changes type of player from human to computer
                                                        // input by human player: ragequit
                        std::cout << "Player" << playerTurn + 1 << " ragequits.  A computer will now take over."  << std::endl;
                        valid = true;
                        table.setIsHuman(playerTurn, false);
                        if (firstPlay) { // first player has to play the 7 of spades
                            std::cout << "Player" << playerTurn + 1 << " plays 7S." << std::endl;
                            firstPlay = false;
                            table.play(playerTurn, 7, 'S');
                        } else { // computer player automatically makes moves
                            table.autoPlay(playerTurn, strat);
                        }
                    } else if (command == "changeStrat") { // change strategy of computer players
                        strat = !strat;
                    } else { // not a valid command
                        std::cout << "Invalid command." << std::endl;
                    }
                }
            } else { // player is a computer
                if (firstPlay) { // first player has to play the 7 of spades
                    std::cout << "Player" << playerTurn + 1 << " plays 7S." << std::endl;
                    firstPlay = false;
                    table.play(playerTurn, 7, 'S');
                } else { // computer player automatically makes moves
                    table.autoPlay(playerTurn, strat);
                }
            }

            if (playerTurn == 3) {
                playerTurn = 0;
            } else {
                ++playerTurn;
            }
        }

        for (int i = 0; i < 4; ++i) {
            std::cout << "Player" << i + 1 << "'s discards:";
            table.printDiscards(i);
            std::cout << std::endl;
            int oldScore = table.getScore(i);
            table.calculateScore(i);
            int newScore = table.getScore(i);
            int scoreGained = newScore - oldScore;
            std::cout << "Player" << i + 1 << "'s score: " << oldScore << " + " << scoreGained << " = " << newScore << std::endl;
        }

        if (table.hasWinners()) {
            gameOver = true;
            int minScore = table.minScore();
            for (int i = 0; i < 4; ++i) {
                if (table.getScore(i) == minScore) std::cout << "Player" << i + 1 << " wins!" << std::endl;
            }
        } else {
            table.reset(); // reset the table to start a new round
        }
    }
    return 0;
}