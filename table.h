#ifndef _TABLE_H_
#define _TABLE_H_
#include "card.h"
#include "deck.h"
#include "player.h"
#include <vector>
#include <memory>

class Player;
class Deck;

class Table {
    std::vector<int> Clubs;
    std::vector<int> Diamonds;
    std::vector<int> Hearts;
    std::vector<int> Spades;
    std::vector<Player> Players;
    Deck CardDeck;

    public:
        // constructor
        Table(bool p1, bool p2, bool p3, bool p4, unsigned seed);

        void deckShuffle(); // shuffles the deck
        void deal(); // deals cards to the players
        int startingPlayer(); // determines index of starting player
        bool emptyHand(int playerTurn); // determines whether a player's hand is empty
        void printTableCards(); // prints cards already played
        void printHand(int playerTurn); // prints the player's hand

        // Legal moves:
        // 1. starting player has to play the 7 of spades
        // 2. any card with rank of 7 is a legal move and starts a new pile
        // 3. card has to have rank ONE less than the lowest rank already played
        //    or ONE more than the highest rank already played
        //    for eg. if 5 6 7 of spades have been played, the only legal moves are:
        //            7 of clubs, 7 of diamonds, 7 of hearts, 4 of spades, 8 of spades
        bool isLegal(int rank, char suit); // checks whether a card is a legal move

        void printLegal(int playerTurn); // prints legal moves in the player's hand
        bool isPlayerHuman(int playerTurn); // checks whether the player is human
        bool cardInHand(int playerTurn, int rank, char suit); // checks whether the card is in the player's hand
        bool hasLegalMoves(int playerTurn); // checks whether the player has any legal moves
        void printDeck(); // prints the deck

        void play(int playerTurn, int rank, char suit); // plays the card with given rank and suit
        void discard(int playerTurn, int rank, char suit); // discards the card with given rank and suit
        void setIsHuman(int playerTurn, bool isPlayerHuman); // sets isHuman for the player
        void autoPlay(int playerTurn, bool strat); // plays the first legal move or discards the first card automatically

        void printDiscards(int playerTurn); // prints cards discarded by player
        int getScore(int playerTurn); // returns the score of the player
        void calculateScore(int playerTurn); // calculates the new score of the player

        bool hasWinners(); // checks whether any player has score >= 80
        int minScore(); // returns minimum score of the players
        void reset(); // resets the table

        char intToRank(int rank); // convertor from int (rank stored as int in Card) to char for rank

    private:
        void printVectorOfCards(std::vector<int> vec); // prints the vector of cards already played
        void addToTable(int rank, char suit); // adds card with given rank and suit to table
};

#endif