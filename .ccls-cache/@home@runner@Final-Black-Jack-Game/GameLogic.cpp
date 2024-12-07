#include "GameLogic.h"
#include "Player.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Helper function to evaluate the winner
void evaluateWinner(const vector<Card>& playerHand, const vector<Card>& dealerHand) 
{
    int playerTotal = calculateHandValue(playerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (playerTotal > 21) 
    {
        cout << "You bust! Dealer wins.\n";
    }
    else if (dealerTotal > 21) 
    {
        cout << "Dealer busts! Player wins.\n";
    }
    else if (playerTotal > dealerTotal) 
    {
        cout << "Player wins with " << playerTotal << "!\n";
    }
    else if (playerTotal < dealerTotal) 
    {
        cout << "Dealer wins.\n";
    }
    else 
    {
        cout << "It's a push!\n";
    }
}

// Function to calculate the value of a hand
int calculateHandValue(const vector<Card>& hand) 
{
    int total = 0;  // Total hand value
    int aces = 0;   // Count of Aces in the hand

    for (const auto& card : hand) 
    {
        string rank = card.getRank();

        if (rank == "Jack" || rank == "Queen" || rank == "King") 
        {
            total += 10;  // Face cards are worth 10
        } 
        else if (rank == "Ace") 
        {
            total += 11;  // Assume Ace is worth 11 initially
            aces++;
        } 
        else 
        {
            total += stoi(rank);  // Convert numeric ranks to integers
        }
    }

    // Adjust for Aces if total exceeds 21
    while (total > 21 && aces > 0) 
    {
        total -= 10;  // Change an Ace from 11 to 1
        aces--;
    }

    return total;
}
//Dealer's Turn
bool dealerTurn(Deck& deck, vector<Card>& dealerHand) 
{
    cout << "\nDealer's hand:" << endl;
    for (const auto& card : dealerHand) card.displayCard();

    while (calculateHandValue(dealerHand) < 17) 
    {
        cout << "\nDealer hits." << endl;

        // Dealer draws a card
        Card newCard = deck.dealCard();
        dealerHand.push_back(newCard);

        // Show the new card
        cout << "Dealer drew: ";
        newCard.displayCard();

        // Show updated total
        int total = calculateHandValue(dealerHand);
        cout << "Dealer's total: " << total << endl;
    }

    int total = calculateHandValue(dealerHand);
    cout << "\nDealer stands with a total of " << total << ".\n";

    if (total > 21) 
    {
        cout << "\nDealer busts. Player wins!\n";
        return false; // Dealer loses
    }
    else return true; // Dealer stands

}

// Helper function for splitting
void splitHands(Deck& deck, vector<Card>& originalHand, vector<Card>& dealerHand) 
{
    if (originalHand.size() != 2 || originalHand[0].getRank() != originalHand[1].getRank()) 
    {
        cout << "Splitting not possible. Hands must contain two cards of the same rank.\n";
        return;
    }

    // Create two split hands
    vector<Card> hand1 = {originalHand[0], deck.dealCard()};
    vector<Card> hand2 = {originalHand[1], deck.dealCard()};

    // Play the first split hand
    cout << "\nPlaying first split hand:\n";

    double bustProb1 = 0.0, to21Prob1 = 0.0, notBustingProb1 = 0.0;
    calculatePlayerProbabilities(hand1, deck, bustProb1, to21Prob1, notBustingProb1);

    cout << fixed << setprecision(2);
    cout << "First Hand - Probability of Busting if you hit: " << bustProb1 * 100 << "%\n";
    cout << "First Hand - Probability of hitting 21 if you hit: " << to21Prob1 * 100 << "%\n";
    cout << "First Hand - Probability of staying under 21: " << notBustingProb1 * 100 << "%\n";

    bool playerDoubledDown1 = false;
    bool hand1InGame = playerTurn(deck, hand1, playerDoubledDown1);
    int total1 = calculateHandValue(hand1);

    if (hand1InGame) 
    {
        cout << "Final total for first hand: " << total1 << endl;
    }
    else 
    {
        cout << "First hand busts with a total of " << total1 << endl;
    }

    // Play the second split hand
    cout << "\nPlaying second split hand:\n";

    double bustProb2 = 0.0, to21Prob2 = 0.0, notBustingProb2 = 0.0;
    calculatePlayerProbabilities(hand2, deck, bustProb2, to21Prob2, notBustingProb2);

    cout << "Second Hand - Probability of Busting if you hit: " << bustProb2 * 100 << "%\n";
    cout << "Second Hand - Probability of hitting 21 if you hit: " << to21Prob2 * 100 << "%\n";
    cout << "Second Hand - Probability of staying under 21: " << notBustingProb2 * 100 << "%\n";

    bool playerDoubledDown2 = false;
    bool hand2InGame = playerTurn(deck, hand2, playerDoubledDown2);
    int total2 = calculateHandValue(hand2);

    if (hand2InGame) 
    {
        cout << "Final total for second hand: " << total2 << endl;
    }
    else 
    {
        cout << "Second hand busts with a total of " << total2 << endl;
    }

    // Dealer's turn and evaluation
    cout << "\nDealer's turn:\n";
    bool dealerStand = dealerTurn(deck, dealerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (!dealerStand) 
    {
        cout << "Dealer busts! ";
        if (hand1InGame) cout << "First hand wins. ";
        if (hand2InGame) cout << "Second hand wins.\n";
    }
    else 
    {
        if (hand1InGame && total1 > dealerTotal && total1 <= 21) 
        {
            cout << "First hand wins against the dealer.\n";
        }
        else if (hand1InGame && total1 == dealerTotal) 
        {
            cout << "First hand ties with the dealer.\n";
        }
        else if (total1 > 21 || total1 < dealerTotal) 
        {
            cout << "First hand loses to the dealer.\n";
        }

        if (hand2InGame && total2 > dealerTotal && total2 <= 21) 
        {
            cout << "Second hand wins against the dealer.\n";
        }
        else if (hand2InGame && total2 == dealerTotal) 
        {
            cout << "Second hand ties with the dealer.\n";
        }
        else if (total2 > 21 || total2 < dealerTotal) 
        {
            cout << "Second hand loses to the dealer.\n";
        }
    }
    //Clears all hands
    originalHand.clear();
}
void calculatePlayerProbabilities(const std::vector<Card>& playerHand, const Deck& deck, double& bustProbability, double& to21Probability, double& notBustingProbability) 
{
    int playerTotal = calculateHandValue(playerHand);
    int cardsToBust = 0;
    int cardsTo21 = 0;

    for (const auto& card : deck.getRemainingCards()) 
    {
        int cardValue = card.getValue();
        if (playerTotal + cardValue > 21) 
        {
            cardsToBust++;
        } else if (playerTotal + cardValue == 21) 
        {
            cardsTo21++;
        }
    }

    int remainingCards = deck.getDeckSize();
    bustProbability = remainingCards > 0 ? static_cast<double>(cardsToBust) / remainingCards : 0.0;
    to21Probability = remainingCards > 0 ? static_cast<double>(cardsTo21) / remainingCards : 0.0;
    notBustingProbability = 1.0 - bustProbability; // Odds of not busting
}