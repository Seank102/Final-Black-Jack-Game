#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

int calculateHandValue(const std::vector<Card>& hand);
void splitHands(Deck& deck, std::vector<Card>& originalHand, std::vector<Card>& dealerHand);
bool dealerTurn(Deck& deck, std::vector<Card>& dealerHand);
void evaluateWinner(const std::vector<Card>& playerHand, const std::vector<Card>& dealerHand);
void calculatePlayerProbabilities(const std::vector<Card>& playerHand, const Deck& deck, double& bustProbability, double& to21Probability, double& notBustingProbability);

#endif
