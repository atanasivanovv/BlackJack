#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "String.h"
#include "Vector.h"
#include <fstream>

using namespace std;

/* 
	Values:         { 1 == 'A', 11 == 'J', 12 == 'Q', 13 == 'K' }
	Suits:  { 1 == "CLUBS", 2 == "DIAMONDS", 3 == "HEARTS", 4 == "SPADES } 
*/


void chooseDeck(bool& whichDeck, int& num) {
	char deck;
	int cardsCount;
	
	cout << "   WHAT DECK DO YOU WANT TO PLAY WITH? " << endl;
	cout << "   -> A: DEFAULT (52 cards) " << endl;
	cout << "   -> B: CUSTOM" << endl;

	cout << "   YOUR CHOICE: ";
	cin >> deck;

	while (deck != 'A' && deck != 'B')
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "   WRONG INPUT" << endl; 
		cout << "   YOUR CHOICE: ";
		cin >> deck;
	}
	
	if (deck == 'A')
	{
		cout << "   ------------------ CREATING A DEFAULT DECK... ------------------  " << endl;
		cout << endl;
		whichDeck = true;
	}
	else
	{
		cout << "   HOW MANY CARDS DO YOU WANT TO PLAY WITH? " << endl;
		cout << "   -> ";
		cin >> cardsCount;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "   INVALID INPUT!" << endl;
			cout << "   HOW MANY CARDS DO YOU WANT TO PLAY WITH? " << endl;
			cout << "   -> ";
			cin >> cardsCount;
		}

		while (cardsCount >= 408)
		{
			cout << "   INVALID INPUT!" << endl;
			cout << "   HOW MANY CARDS DO YOU WANT TO PLAY WITH? " << endl;
			cout << "   -> ";
			cin >> cardsCount;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "   INVALID INPUT!" << endl;
				cout << "   HOW MANY CARDS DO YOU WANT TO PLAY WITH? " << endl;
				cout << "   -> ";
				cin >> cardsCount;
			}
		}


		num = cardsCount;
		cout << endl;

		cout << "   ------------------ CREATING A DECK WITH " << cardsCount << " CARDS... ------------------  " << endl;
		whichDeck = false;
	}
		
}

int aceCheck()
{
	int aceValue;
	cout << "   YOU HAVE DRAWN AN ACE." << endl;
	cout << "   YOU CAN CHOOSE TO ADD EITHER 1 OR 11 POINTS:" << endl;
	cout << "   -> ";
	cin >> aceValue;

	while (aceValue != 11 && aceValue != 1)
	{
		cout << "ENTER EITHER 1 OR 11!" << endl;
		cout << "   -> ";
		cin.clear();
		cin.ignore(132, '\n');
		cin >> aceValue;
	}

	return aceValue;
}

void hitOrStand (char &playerChoice) 
{
	cout << "   YOU CAN EITHER HIT OR STAND... " << endl;
	cout << "   -> A: HIT " << endl;
	cout << "   -> B: STAND" << endl;
	cout << "   -> C: PROBABILITY" << endl;
	cout << "   YOUR CHOICE: ";

	cin >> playerChoice; cout << endl;

	while (playerChoice != 'B' && playerChoice != 'b' && playerChoice != 'A' && playerChoice != 'a' && playerChoice != 'C' && playerChoice != 'c')
	{
		cin.clear();
		cin.ignore(132, '\n');
		cout << "   INCORRECT INPUT " << endl;
		cout << "   -> A: HIT " << endl;
		cout << "   -> B: STAND" << endl;
		cout << "   -> C: PROBABILITY" << endl;
		cout << "   YOUR CHOICE: ";
		cin >> playerChoice; cout << endl;
	}
}

void showPoints(const int playerPoints, const int opponentPoints)
{
	cout << "   YOUR POINTS: ";
	cout << playerPoints;
	cout << endl << endl;

	cout << "   OPPONENT POINTS: ";
	cout << opponentPoints; cout << endl << endl;
}

void decideWinner(Player& startPlayer, Player& opponent) {
	if (opponent.getCurrentPoints() > 21)
	{
		cout << "   THE OPPONENT GOT ABOVE 21 - YOU WIN!" << endl;
		startPlayer.addWin();
	}
	else if (opponent.getCurrentPoints() == 21)
		cout << "   THE OPPONENT GOT 21 - YOU LOSE!" << endl;
	else if (startPlayer.getCurrentPoints() > 21)
		cout << "   YOU GOT ABOVE 21 - YOU LOSE!" << endl;
	else if (startPlayer.getCurrentPoints() == 21)
	{
		cout << "   YOU GOT 21 - YOU WIN!" << endl;
		startPlayer.addWin();
	}
	else if (startPlayer.getCurrentPoints() >= opponent.getCurrentPoints())
	{
		cout << "   YOU HAVE MORE POINTS - YOU WIN!" << endl;
		startPlayer.addWin();
	}
	else if (startPlayer.getCurrentPoints() < opponent.getCurrentPoints())
		cout << "   THE OPPONENT HAS MORE POINTS - YOU LOSE!" << endl;

	cout << endl;
}

int main()
{
	srand(time(NULL));

	Vector<Player> registeredUsers;

	cout << "   ------------------    WELCOME TO BLACKJACK    ------------------   " << endl;

	if (registeredUsers.getSize() >= 1)
	{
		for (size_t i = 0; i < registeredUsers.getSize(); i++)
			registeredUsers[i].print();
	}
			

	Player startPlayer;
	Player opponent;
	bool deckChoise;
	int numOfCards = 0;

	startPlayer.reg();

	if (startPlayer.getPlayerValidation())
	{
		chooseDeck(deckChoise, numOfCards); 
			

		// DEFAULT DECK
		if (deckChoise)
		{
			// With default deck
			Deck defaultDeck;

			// The player draws a card
			Card drawnCard = defaultDeck.getDrawnCard();
			defaultDeck.draw();
			cout << "   YOU DREW  ->  ";
			drawnCard.printCard(); cout << endl;
			startPlayer.setDrawnCard(drawnCard);

			// The opponent draws a card
			Card opponentDrawnCard = defaultDeck.getDrawnCard();
			defaultDeck.draw();
			cout << "   YOU OPPENENT DREW  ->  ";
			opponentDrawnCard.printCard(); cout << endl;
			opponent.setDrawnCard(opponentDrawnCard);

			// Adding the points to the player
			if (drawnCard.getValue() == 1)
			{
				if (aceCheck() == 1)
					startPlayer.setCurrentPoints(1);
				else 
					startPlayer.setCurrentPoints(11);
			}
			else 
				startPlayer.addPoints(drawnCard);

			opponent.addPoints(opponentDrawnCard);

			showPoints(startPlayer.getCurrentPoints(), opponent.getCurrentPoints());
				
			// HIT OR STAND
			char playerChoice;
			cout << "   ------------------    HIT OR STAND    ------------------   " << endl << endl;		

			while (startPlayer.getCurrentPoints() < 21 && opponent.getCurrentPoints() < 21)
			{
				hitOrStand(playerChoice);

				if (playerChoice == 'A' || playerChoice == 'a')
				{
					// Drawing a card
					Card secondDrawnCard = defaultDeck.getDrawnCard();
					defaultDeck.draw();
					cout << "   YOU DREW  ->  ";
					secondDrawnCard.printCard(); cout << endl;

					// Adding the points to the player
					startPlayer.addPoints(secondDrawnCard);

					// Showing the points
					showPoints(startPlayer.getCurrentPoints(), opponent.getCurrentPoints());
				}
				else if (playerChoice == 'B' || playerChoice == 'b')
				{
					cout << "   ------------------    DRAWING CARDS FOR THE OPPONENT...    ------------------   " << endl << endl;

					while (opponent.getCurrentPoints() < 17)
					{
						// Drawing a card
						Card opponentSecondDrawnCard = defaultDeck.getDrawnCard();
						defaultDeck.draw();
						cout << "   YOUR OPPONENT DREW  ->  ";
						opponentSecondDrawnCard.printCard(); cout << endl;

						// Adding the points to the opponent
						opponent.addPoints(opponentSecondDrawnCard);

						// Showing the points
						showPoints(startPlayer.getCurrentPoints(), opponent.getCurrentPoints());
					}

					break;
				}
				else
				{
					// If the player chooses probabilty
					int collectedPoints = startPlayer.getCurrentPoints();
					int leftPointsTo21 = 21 - collectedPoints;
					size_t perfectCards = defaultDeck.rank_count(leftPointsTo21);

					double probability =  perfectCards / defaultDeck.getSize();

					if (leftPointsTo21 > 11)
						probability = 0;

					cout << "   PROBABILITY OF COMPLETING YOUR SCORE TO 21: " << endl; cout << "   -> ";
					cout << probability << endl;
				}
			}

			cout << "   ------------------    THE GAME HAS ENDED...    ------------------   " << endl << endl;

			// Depending on the points
			decideWinner(startPlayer, opponent);

			cout << "   ------------------    PLAYER STATISTICS...    ------------------   " << endl << endl;
			startPlayer.addGamePlayed();
			startPlayer.updateWinOdd();
			registeredUsers.push_back(startPlayer);

			// Reseting the stats
			startPlayer.setCurrentPoints(0);
			opponent.setCurrentPoints(0);

			// After updating stats, output the player stats into a file 
			fstream fs;
			startPlayer.printOutput(fs); cout << endl;

			cout << "   Saved player stats into registeredUsers for: "; startPlayer.getName();
			startPlayer.printStats(); cout << endl;

			cout << "   ------------------    QUITTING THE GAME...    ------------------   " << endl << endl;

		}







		// CUSTOM DECK
		else  
		{
			// With custom deck
			Deck customDeck(numOfCards);

			// The player draws a card
			Card drawnCard = customDeck.getDrawnCard();
			customDeck.draw();
			cout << "   YOU DREW  ->  ";
			drawnCard.printCard(); cout << endl;
			startPlayer.setDrawnCard(drawnCard);

			// The opponent draws a card
			Card opponentDrawnCard = customDeck.getDrawnCard();
			customDeck.draw();
			cout << "   YOU OPPENENT DREW  ->  ";
			opponentDrawnCard.printCard(); cout << endl;
			opponent.setDrawnCard(opponentDrawnCard);

			// Adding the points to the player
			if (drawnCard.getValue() == 1)
			{
				if (aceCheck() == 1)
					startPlayer.setCurrentPoints(1);
				else
					startPlayer.setCurrentPoints(11);
			}
			else
				startPlayer.addPoints(drawnCard);

			cout << "   YOUR POINTS: ";
			cout << startPlayer.getCurrentPoints();
			cout << endl << endl;

			// Adding the points to the opponent
			opponent.addPoints(opponentDrawnCard);
			cout << "   OPPONENT POINTS: ";
			cout << opponent.getCurrentPoints();
			cout << endl;

			// HIT OR STAND
			char playerChoice;
			cout << "   ------------------    HIT OR STAND    ------------------   " << endl << endl;

			while (startPlayer.getCurrentPoints() < 21 && opponent.getCurrentPoints() < 21)
			{
				hitOrStand(playerChoice);

				if (playerChoice == 'A' || playerChoice == 'a')
				{
					// Drawing a card
					Card secondDrawnCard = customDeck.getDrawnCard();
					customDeck.draw();
					cout << "   YOU DREW  ->  ";
					secondDrawnCard.printCard(); cout << endl;

					// Adding the points to the player
					startPlayer.addPoints(secondDrawnCard);

					// Showing the points
					showPoints(startPlayer.getCurrentPoints(), opponent.getCurrentPoints());
				}
				else if (playerChoice == 'B' || playerChoice == 'b')
				{
					/* ÎÏÎÍÅÍÒÀ ÏÎ×ÂÀ ÄÀ ÒÅÃËÈ ÄÎÊÀÒÎ ÍÅ ÑÒÈÃÍÅ 17 */

					cout << "   ------------------    DRAWING CARDS FOR THE OPPONENT...    ------------------   " << endl << endl;

					while (opponent.getCurrentPoints() < 17)
					{
						// Drawing a card
						Card opponentSecondDrawnCard = customDeck.getDrawnCard();
						customDeck.draw();
						cout << "   YOUR OPPONENT DREW  ->  ";
						opponentSecondDrawnCard.printCard(); cout << endl;

						// Adding the points to the opponent
						opponent.addPoints(opponentSecondDrawnCard);

						// Showing the points
						showPoints(startPlayer.getCurrentPoints(), opponent.getCurrentPoints());
					}

					break;
				}
				else
				{
					// If the player chooses probabilty
					int collectedPoints = startPlayer.getCurrentPoints();
					int leftPointsTo21 = 21 - collectedPoints;
					size_t perfectCards = customDeck.rank_count(leftPointsTo21);

					double probability = perfectCards / customDeck.getSize();

					if (leftPointsTo21 > 11)
						probability = 0;

					cout << "   PROBABILITY OF COMPLETING YOUR SCORE TO 21: " << endl; cout << "   -> ";
					cout << probability << endl << endl;
				}
			}

			cout << "   ------------------    THE GAME HAS ENDED...    ------------------   " << endl << endl;

			// Depending on the points
			decideWinner(startPlayer, opponent);

			cout << "   ------------------    PLAYER STATISTICS...    ------------------   " << endl << endl;
			startPlayer.addGamePlayed();
			startPlayer.updateWinOdd();
			registeredUsers.push_back(startPlayer);

			// Reseting the stats
			startPlayer.setCurrentPoints(0);
			opponent.setCurrentPoints(0);

			// After updating stats, output the player stats into a file 
			fstream fs;
			startPlayer.printOutput(fs); cout << endl;

			cout << "   Saved player stats into registeredUsers for: "; startPlayer.getName();
			startPlayer.printStats(); cout << endl;

			cout << "   ------------------    QUITTING THE GAME...    ------------------   " << endl << endl;

			// Reseting the stats
			startPlayer.setCurrentPoints(0);
			opponent.setCurrentPoints(0);
		}	
	}
	else
	{
		cout << endl;
		cout << "   Error registering player!" << endl;
	}
}

