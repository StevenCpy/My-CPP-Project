#include "deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>

// constructor for Deck
Deck::Deck(unsigned seed): Seed{seed} {
    // adds 52 Card(s) to the Deck in the following order:
    // AC, 2C, ..., 9C, TC, JC, QC, KC, AD, 2D, ..., KD, AH, 2H, ..., KH, AS, 2S, ..., KS
    for (int i = 1; i <= 13; ++i) {
        std::shared_ptr<Card> card = card->cardCreate(i, 'C'); // <rank> of Clubs
        Cards.emplace_back(card);
    }
    for (int i = 1; i <= 13; ++i) {
        std::shared_ptr<Card> card = card->cardCreate(i, 'D'); // <rank> of Diamonds
        Cards.emplace_back(card);
    }
    for (int i = 1; i <= 13; ++i) {
        std::shared_ptr<Card> card = card->cardCreate(i, 'H'); // <rank> of Hearts
        Cards.emplace_back(card);
    }
    for (int i = 1; i <= 13; ++i) {
        std::shared_ptr<Card> card = card->cardCreate(i, 'S'); // <rank> of Spades
        Cards.emplace_back(card);
    }
}

// returns a shared_ptr to the card at index
std::shared_ptr<Card> Deck::getDeckCard(int index) { return Cards[index]; }

// prints each card in the deck in the order in which they appear (13 cards per line)
void Deck::printDeck() {
    for (int i = 0; i < 52; ++i) {
        Cards[i]->printCard();
        if (i == 12 || i == 25 || i == 38 || i == 51) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
    }
}

// shuffles the deck using the field Seed
void Deck::Shuffle() {
    std::default_random_engine rng{Seed};

    std::shuffle(Cards.begin(), Cards.end(), rng);
}