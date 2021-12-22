#include "table.h"
#include <iostream>
#include <vector>
#include <memory>

// constructor for Table
Table::Table(bool p1, bool p2, bool p3, bool p4, unsigned seed): CardDeck{Deck(seed)} {
    // adds 4 Player(s) to the Table
    Player player1 = player1.playerCreate(p1);
    Players.emplace_back(player1);
    Player player2 = player2.playerCreate(p2);
    Players.emplace_back(player2);
    Player player3 = player3.playerCreate(p3);
    Players.emplace_back(player3);
    Player player4 = player4.playerCreate(p4);
    Players.emplace_back(player4);
}

// shuffles the Deck from Table
void Table::deckShuffle() {
    CardDeck.Shuffle();
    return;
}

// deals the first 13 Card(s) in CardDeck to the 1st Player, the next 13 to the 2nd Player,
// the next 13 to the 3rd Player and the last 13 to the 4th Player.
void Table::deal() {
    for (int i = 0; i < 4; ++i) {
        for (int j = i*13; j < (i+1)*13; ++j) {
            std::shared_ptr<Card> card = CardDeck.getDeckCard(j);
            Players[i].addHandCard(card);
        }
    }
    return;
}

// returns the index of the starting Player based on who has the 7 of spades
// the first Player has index 0 and the 4th Player has index 3
int Table::startingPlayer() {
    int starting;
    // for each Player
    for (int i = 0; i < 4; ++i) {
        // for each Card in the current Player's Hand
        for (int j = 0; j < Players[i].handSize(); ++j) {
            std::shared_ptr<Card> card = Players[i].getHandCard(j);
            if (card->getRank() == 7 && card->getSuit() == 'S') starting = i;
        }
    }
    return starting;
}

// determines whether or not the Player's Hand is empty
// returns true if empty
bool Table::emptyHand(int playerTurn) { return (Players[playerTurn].handSize() == 0); }

// given a vector of integers for Cards(s) already played for a given suit,
// prints the Card(s)
void Table::printVectorOfCards(std::vector<int> vec) {
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << " ";
        if (vec[i] == 1) {
            std::cout << 'A';
        } else if (vec[i] == 10) {
            std::cout << 'T';
        } else if (vec[i] == 11) {
            std::cout << 'J';
        } else if (vec[i] == 12) {
            std::cout << 'Q';
        } else if (vec[i] == 13) {
            std::cout << 'K';
        } else {
            std::cout << vec[i];
        }
    }
    std::cout << std::endl;
    return;
}

// same as printVectorOfCards(vec) but repeated for each Suit
void Table::printTableCards() {
    std::cout << "Clubs:";
    printVectorOfCards(Clubs);
    std::cout << "Diamonds:";
    printVectorOfCards(Diamonds);
    std::cout << "Hearts:";
    printVectorOfCards(Hearts);
    std::cout << "Spades:";
    printVectorOfCards(Spades);
    return;
}

// prints the Hand of the Player
void Table::printHand(int playerTurn) {
    Players[playerTurn].printHand();
    return;
}

// returns whether or not a Card with a given rank and suit is a legal move
// see table.h for details about legal moves
bool Table::isLegal(int rank, char suit) {
    // a card with a rank of 7 is always a legal move
    if (rank == 7) return true;
    if (suit == 'C') {
        // list of Card(s) already played in Clubs is not empty
        if (Clubs.empty()) return false;
        // Card must have rank one less than the lowest rank already played,
        // or one more than the highest rank already played in Clubs
        if (rank == Clubs[0] - 1 || rank == Clubs[Clubs.size()-1] + 1) return true;
    } else if (suit == 'D') {
        // list of Card(s) already played in Diamonds is not empty
        if (Diamonds.empty()) return false;
        // Card must have rank one less than the lowest rank already played,
        // or one more than the highest rank already played in Diamonds
        if (rank == Diamonds[0] - 1 || rank == Diamonds[Diamonds.size()-1] + 1) return true;
    } else if (suit == 'H') {
        // list of Card(s) already played in Hearts is not empty
        if (Hearts.empty()) return false;
        // Card must have rank one less than the lowest rank already played,
        // or one more than the highest rank already played in Hearts
        if (rank == Hearts[0] - 1 || rank == Hearts[Hearts.size()-1] + 1) return true;
    } else {
        // list of Card(s) already played in Spades is not empty
        if (Spades.empty()) return false;
        // Card must have rank one less than the lowest rank already played,
        // or one more than the highest rank already played in Spades
        if (rank == Spades[0] - 1 || rank == Spades[Spades.size()-1] + 1) return true;
    }
    return false; // not a legal move
}

// prints legal moves in the Player's Hand
void Table::printLegal(int playerTurn) {
    // for each Card in Player's Hand
    for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
        std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
        // if move is legal
        if (isLegal(card->getRank(), card->getSuit())) {
            std::cout << " ";
            card->printCard();
        }
    }
    return;
}

// returns isHuman for the Player at PlayerTurn
bool Table::isPlayerHuman(int playerTurn) { return Players[playerTurn].getIsHuman(); }

// checks whether the Card with given rank and suit is in the Player's Hand
bool Table::cardInHand(int playerTurn, int rank, char suit) {
    for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
        std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
        if (card->getRank() == rank && card->getSuit() == suit) return true;
    }
    return false;
}

// returns whether or not the Player at playerTurn has any legal moves
bool Table::hasLegalMoves(int playerTurn) {
    for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
        std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
        if (isLegal(card->getRank(), card->getSuit())) return true;
    }
    return false;
}

// prints the Deck
void Table::printDeck() { CardDeck.printDeck(); }

// when the Card with given rank and suit is played, add the rank
// to the respective vectors of Card(s) already played
void Table::addToTable(int rank, char suit) {
    if (suit == 'C') {
        if (rank == 7) {
            Clubs.push_back(rank); // adds the rank to the empty vector
        } else if (rank < Clubs[0]) { // rank is one less than lowest rank
            Clubs.insert(Clubs.begin() + 0, rank); // adds the rank to the beginning of vector
        } else {
            Clubs.push_back(rank); // adds the rank to the end of the vector
        }
    } else if (suit == 'D') {
        if (rank == 7) {
            Diamonds.push_back(rank); // adds the rank to the empty vector
        } else if (rank < Diamonds[0]) { // rank is one less than lowest rank
            Diamonds.insert(Diamonds.begin() + 0, rank); // adds the rank to the beginning of vector
        } else {
            Diamonds.push_back(rank); // adds the rank to the end of the vector
        }
    } else if (suit == 'H') {
        if (rank == 7) {
            Hearts.push_back(rank); // adds the rank to the empty vector
        } else if (rank < Hearts[0]) { // rank is one less than lowest rank
            Hearts.insert(Hearts.begin() + 0, rank); // adds the rank to the beginning of vector
        } else {
            Hearts.push_back(rank); // adds the rank to the end of the vector
        }
    } else {
        if (rank == 7) {
            Spades.push_back(rank); // adds the rank to the empty vector
        } else if (rank < Spades[0]) { // rank is one less than lowest rank
            Spades.insert(Spades.begin() + 0, rank); // adds the rank to the beginning of vector
        } else {
            Spades.push_back(rank); // adds the rank to the end of the vector
        }
    }
}

// removes the Card with given rank and suit from the Player's Hand
// and adds it to the respective vector for Card(s) already played
void Table::play(int playerTurn, int rank, char suit) {
    for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
        std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
        if (card->getRank() == rank && card->getSuit() == suit) {
            addToTable(rank, suit); // adds Card to respective vector for Card(s) already played
            Players[playerTurn].removeHandCard(i); // removes Card from Player's Hand
            return;
        }
    }
}

// removes the Card with given rank and suit from the Player's Hand
// and adds it to the Player's Discards
void Table::discard(int playerTurn, int rank, char suit) {
    for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
        std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
        if (card->getRank() == rank && card->getSuit() == suit) {
            Players[playerTurn].addDiscardsCard(card); // adds Card to Player's Discards
            Players[playerTurn].removeHandCard(i); // removes Card from Player's Hand
            return;
        }
    }
}

// sets isHuman for the Player at playerTurn to isPlayerHuman
void Table::setIsHuman(int playerTurn, bool isPlayerHuman) {
    Players[playerTurn].setIsHuman(isPlayerHuman);
    return;
}

// converts the rank of an int to its corresponding char value
char Table::intToRank(int rank) {
    if (rank == 1) return 'A';
    if (rank == 10) return 'T';
    if (rank == 11) return 'J';
    if (rank == 12) return 'Q';
    if (rank == 13) return 'K';
    return '0' + rank;
}

// plays first legal move or discards first Card automatically
void Table::autoPlay(int playerTurn, bool strat) {
    if (hasLegalMoves(playerTurn)) { // Player has legal moves
        // look for first legal move in the Player's Hand

        if (strat) { // plays highest card
            int max = 1;
            for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
                std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
                if (isLegal(card->getRank(), card->getSuit()) && (card->getRank() > max)) max = card->getRank();
            }
            for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
                std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
                if (isLegal(card->getRank(), card->getSuit()) && (card->getRank() == max)) {
                    std::cout << "Player" << playerTurn + 1 << " plays " << intToRank(card->getRank()) << card->getSuit() << "." << std::endl;
                    play(playerTurn, card->getRank(), card->getSuit()); // plays the Card
                    return;
                }
            }
        } else {
            for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
                std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
                if (isLegal(card->getRank(), card->getSuit())) {
                    std::cout << "Player" << playerTurn + 1 << " plays " << intToRank(card->getRank()) << card->getSuit() << "." << std::endl;
                    play(playerTurn, card->getRank(), card->getSuit()); // plays the Card
                    return;
                }
            }
        }
    } else {
        if (strat) { // discards lowest card
            int min = 13;
            for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
                std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
                if (card->getRank() < min) min = card->getRank();
            }
            for (int i = 0; i < Players[playerTurn].handSize(); ++i) {
                std::shared_ptr<Card> card = Players[playerTurn].getHandCard(i);
                if (card->getRank() == min) {
                    std::cout << "Player" << playerTurn + 1 << " discards " << intToRank(card->getRank()) << card->getSuit() << "." << std::endl;
                    discard(playerTurn, card->getRank(), card->getSuit()); // discards the lowest Card in the Player's Hand
                    return;
                }
            }
        } else {
            std::shared_ptr<Card> card = Players[playerTurn].getHandCard(0);
            std::cout << "Player" << playerTurn + 1 << " discards " << intToRank(card->getRank()) << card->getSuit() << "." << std::endl;
            discard(playerTurn, card->getRank(), card->getSuit()); // discards the first Card in the Player's Hand
        }
    }
    return;
}

// prints the Discards of the Player at playerTurn
void Table::printDiscards(int playerTurn) {
    Players[playerTurn].printDiscards();
    return;
}

// returns the current Score of the Player at playerTurn
int Table::getScore(int playerTurn) { return Players[playerTurn].getScore(); }

// calculates the new Score of the Player at playerTurn
void Table::calculateScore(int playerTurn) {
    Players[playerTurn].calculateScore();
    return;
}

// checks whether any Player has a Score >= 80
// true if at least one Player has Score >= 80
bool Table::hasWinners() {
    for (int i = 0; i < 4; ++i) {
        int score = Players[i].getScore();
        if (score >= 80) return true;
    }
    return false;
}

// returns the minimum Score of all Player(s)
int Table::minScore() {
    int min = getScore(0);
    for (int i = 0; i < 4; ++i) {
        if (getScore(i) <= min) min = getScore(i);
    }
    return min;
}

// resets each Player's Discards and vectors of Card(s) already played
void Table::reset() {
    while (!Clubs.empty()) Clubs.pop_back();
    while (!Diamonds.empty()) Diamonds.pop_back();
    while (!Hearts.empty()) Hearts.pop_back();
    while (!Spades.empty()) Spades.pop_back();
    for (int i = 0; i < 4; ++i) {
        Players[i].reset();
    }
    return;
}