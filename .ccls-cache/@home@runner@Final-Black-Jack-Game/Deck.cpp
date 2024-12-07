#include "Deck.h"
#include <stdexcept>
#include <random>
#include <algorithm>
using namespace std;

// Creates a deck with 52 cards
Deck::Deck() 
{
    static_assert(CLUBS < DIAMONDS, "Suit enum values are not ordered properly."); // Error checking against unwanted suit changes
    static_assert(TWO < ACE, "Rank enum values are not ordered properly."); // Error checking against unwanted rank changes

    for (int s = CLUBS; s <= DIAMONDS; ++s) 
    {   // Loop through all suits
        for (int r = TWO; r <= ACE; ++r) 
        {    // Loops through all ranks and links suit and rank
            cards.push_back(Card(static_cast<Rank>(r), static_cast<Suit>(s)));
        }
    }
}

// Resets the deck by clearing and re-looping suit rank
void Deck::resetDeck() 
{
    cards.clear();  // Clear the current deck
    for (int s = CLUBS; s <= DIAMONDS; ++s) 
    {   // Loop through all suits
        for (int r = TWO; r <= ACE; ++r) 
        {  // Loop through all ranks
            cards.push_back(Card(static_cast<Rank>(r), static_cast<Suit>(s)));
        }
    }
    shuffleDeck();  // Shuffle the deck after resetting
}

// Shuffles the deck using a random number generator
void Deck::shuffleDeck() 
{
    random_device rd;    // Seed for random number generator
    mt19937 g(rd());     // Mersenne Twister RNG
    shuffle(cards.begin(), cards.end(), g); // Shuffle the cards
}

// Deals one card from the deck
Card Deck::dealCard() 
{
    if (!cards.empty()) 
    {   // Error checking for empty deck
        Card dealtCard = cards.back(); // Get the top card
        cards.pop_back();              // Remove the top card from the stack
        return dealtCard;              // Return the dealt card to the program
    }
    throw runtime_error("No cards left in the deck!"); // Debug error if deck is empty
}

//Debug: Displays all cards in the deck
void Deck::displayDeck() const 
{
    for (const auto& card : cards) 
    {
        card.displayCard();
    }
}

int Deck::getDeckSize() const 
{
    return cards.size();
}

//Debug and probability: Returns the cards remaining in the deck
const std::vector<Card>& Deck::getRemainingCards() const {
    return cards;
}