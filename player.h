#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "card.h"
#include <vector>
#include <memory>

class Card; // forward declaration for Card

class Player {
    bool isHuman; // if true, Player is a human
    std::vector<std::shared_ptr<Card>> Hand; // Hand is a vector of Card(s) with maximum size 13
    std::vector<std::shared_ptr<Card>> Discards; // Discards is a vector of Card(s) with maximum size 13
    int Score; // current Score of the Player

    public:
        // constructor
        Player(bool isHuman);
        
        // gettors
        bool getIsHuman(); // true if Player is human, false if Player is a computer
        int getScore(); // gets the Score of the Player
        std::shared_ptr<Card> getHandCard(int index); // gets the Player's Hand Card at index

        // settor
        void setIsHuman(bool isPlayerHuman); // sets the value of isHuman

        Player playerCreate(bool isHuman); // creates a Player and returns it
        void printHand(); // prints the Hand of the Player
        void printDiscards(); // prints the Discards of the Player
        void calculateScore(); // calculates the new Score of the Player
        void reset(); // resets the Discards of the Player so that a new round can be started

        int handSize(); // returns the number of Card(s) in the Player's Hand
        int discardsSize(); // returns the number of Card(s) the player has discarded
        void addHandCard(std::shared_ptr<Card> card); // adds a shared_ptr to a Card to the Player's Hand
        void removeHandCard(int index); // removes the Card at index from the Player's Hand
        void addDiscardsCard(std::shared_ptr<Card> card); // adds a shared_ptr to a Card to the Player's Discards
};

#endif