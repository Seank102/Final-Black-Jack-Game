BlackJack
This program simulates a fully functional singleplayer, single deck, blackjack game.

This project utilizes most of the main aspects of blackjack. You can split cards, double down, bust, win, and it also shows probabilities.
What we didn't add was anything related with money and might have missed coding for multiple split hands which happens was less often in a single deck BlackJack game. 

The program uses dynamic approaches to make the game feel fluid and alive. The program also dynamically checks aces to be either 1 or 11 to avoid a potential bust.
Probability within the program is controlled by looping through the remaining cards and tallying up the potential busts and potential 21 hits. 
There are 5 files. Deck.cpp creates and manages the deck of 52 cards. Card.cpp creates each card by looping through the values and their respective suits.
Gamelogic evaluates the winner, evaluates the players hand, handles split hands, handles probability and handles the dealers turn.
Player.cpp handles the entire player turn from start to finish aside from splitting hands.  
Main.cpp executes the main game loop.

Authors:
Sean Robertson
Gage Robison

Date Published
12/8/2024

The program works well within replit. If you use another style of compiler you may need to copy the code over to account for their source files.
Instructions:
Once you start the program it will check for blackjack on both dealer and player hands and check for player pairs.
Next it will show both your cards and the dealers first card.
It will prompt if you want to double down which if yes it will pull a card and end your turn prompting the dealers turn.
If no, it will ask if you want to hit or stand.
If you hit, it will recalculate your hand to be sure it didn't bust. 
If it busted you lose and the game will prompt if you'd like to play again.
If you didn't bust it will ask if you want to hit or stand again. 
If you opt for standing this time it will end your turn and prompt the dealers turn.
The dealer will hit until they reach at least a soft 17.
Once the dealer has hit a soft 17 or more, it will stop and check if the dealer is more or less than the player.
This will determine if the player won the round or not. 
Then the program will ask if the player wants to play again continuing or exiting the loop.
