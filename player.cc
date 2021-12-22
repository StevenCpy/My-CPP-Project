#include "player.h"
#include <iostream>
#include <vector>
#include <memory>

// constructor for Player
Player::Player(bool isHuman): isHuman{isHuman}, Score{0} {}

// gettor for IsHuman
bool Player::getIsHuman() { return isHuman; }

// gettor for Score
int Player::getScore() { return Score; }

// returns a shared_ptr to the Card in the player's hand at index
std::shared_ptr<Card> Player::getHandCard(int index) { return Hand[index]; }

// settor for IsHuman
void Player::setIsHuman(bool isPlayerHuman) {
    isHuman = isPlayerHuman;
    return;
}

// creates a Player using the constructor and returns it
Player Player::playerCreate(bool isHuman) {
    Player player{isHuman};
    return player;
}

// prints each Card in the hand of the Player in the order in which they appear
void Player::printHand() {
    for (std::size_t i = 0; i < Hand.size(); ++i) {
        std::cout << " ";
        Hand[i]->printCard();
    }
}

// prints the Player's discarded Card(s) in the order in which they were discarded
void Player::printDiscards() {
     for (std::size_t i = 0; i < Discards.size(); ++i) {
        std::cout << " ";
        Discards[i]->printCard();
    }
}

// settor to set the Player's Score to their new Score
void Player::calculateScore() {
    int roundScore = 0;
    for (std::size_t i = 0; i < Discards.size(); ++i) {
        roundScore += Discards[i]->getRank();
    }
    Score += roundScore;
}

// removes each discarded Card from the Player
void Player::reset() {
    while (!Discards.empty()) {
        Discards.pop_back();
    }
}

// returns the Hand size of the Player
int Player::handSize() { return Hand.size(); }

// returns the Discards size of the Player
int Player::discardsSize() { return Discards.size(); }

// add the shared_ptr to the Card to the Player's Hand
void Player::addHandCard(std::shared_ptr<Card> card) {
    Hand.emplace_back(card);
    return;
}

// remove the Card at index from the Player's Hand
void Player::removeHandCard(int index) {
    Hand.erase(Hand.begin() + index);
    return;
}

// add the shared_ptr to the Card to the Player's Discards
void Player::addDiscardsCard(std::shared_ptr<Card> card) {
    Discards.emplace_back(card);
    return;
}