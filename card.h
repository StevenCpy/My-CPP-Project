#ifndef _CARD_H_
#define _CARD_H_
#include <memory>

class Card {
    int Rank;
    char Suit;
    public:
        // constructor
        Card(int rank, char suit);

        // gettors
        int getRank();
        char getSuit();

        void printCard(); // prints the card
        std::shared_ptr<Card> cardCreate(int rank, char suit); // creates the card and returns a shared_ptr to it
};

#endif