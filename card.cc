#include "card.h"
#include <iostream>
#include <memory>

// constructor for Card
Card::Card(int rank, char suit): Rank{rank}, Suit{suit} {}

// gettor for rank of card
int Card::getRank() { return Rank; }

// gettor for suit of card
char Card::getSuit() { return Suit; }

// print the card: <rank><suit>
void Card::printCard() {
    if (Rank == 1) {
        std::cout << 'A';
    } else if (Rank == 10) {
        std::cout << 'T';
    } else if (Rank == 11) {
        std::cout << 'J';
    } else if (Rank == 12) {
        std::cout << 'Q';
    } else if (Rank == 13) {
        std::cout << 'K';
    } else {
        std::cout << Rank;
    }
    std::cout << Suit;
}

// create a new card and returns a shared_ptr pointer to it
std::shared_ptr<Card> Card::cardCreate(int rank, char suit) { // CORRECTION: returns a shared_ptr to a Card
    auto card = std::make_shared<Card>(rank, suit);
    return card;
}