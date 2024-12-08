#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

// Deck class
class Deck 
{
    private:
        std::vector<Card> cards; // Vector to store the cards in the deck
    public:
        // Constructor to initialize the deck with 52 cards
        Deck();

        // Function to shuffle the deck
        void shuffleDeck();

        // Function to deal one card
        Card dealCard();

        // Function to display all cards in the deck
        void displayDeck() const;

        // Function that resets the deck after each round
        void resetDeck();
        // Function that gets the size of the current deck
        int getDeckSize() const;
        // Function that returns the remaining cards in the current gamestate deck
        const std::vector<Card>& getRemainingCards() const;
};

#endif
