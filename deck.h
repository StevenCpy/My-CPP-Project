#ifndef _DECK_H_
#define _DECK_H_
#include "card.h"
#include <vector>
#include <memory>

class Deck {
    unsigned Seed;
    std::vector<std::shared_ptr<Card>> Cards; // vector of shared_ptr(s) of Card

    public:
        // constructor
        Deck(unsigned seed);
        
        // gettor
        std::shared_ptr<Card> getDeckCard(int index);

        void printDeck(); // prints the deck
        void Shuffle(); // shuffles the deck
};

#endif