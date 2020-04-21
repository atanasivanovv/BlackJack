#pragma once
#include "Deck.h"
#include <fstream>

using namespace std;

class Player {
private:
	char name[64];
	int age;
	int wins;
	double winOdd;
	int currentPoints;
	int gamesPlayed;
	
	bool playerValidation;
	Card drawnCard;

	bool validation()
	{
		for (int i = 0; name[i] != '\0'; i++)
		{
			if (name[0] == ' ')
				return false;

			if (!(name[0] >= 'A' && name[0] <= 'Z'))
				return false;

			if (name[i] == ' ')
			{
				if (!(name[i + 1] >= 'A' && name[i + 1] <= 'Z'))
					return false;
			}
		}

		return true;
	}
public:
	Player();
	Player(const char* name, int age, int wins, double winOdd, int currentPoints);

	bool getPlayerValidation() const;
	void setDrawnCard(const Card drawnCard);
	Card getDrawnCard() const;
	void setCurrentPoints(int points);
	void addPoints(const Card card);
	int  getCurrentPoints() const;

	void addWin();
	void addGamePlayed();
	int getGamesPlayed() const;
	void updateWinOdd();
	int getWinOdd() const;

	void print();
	void printStats();
	void printOutput(fstream& outputStream);
	void getName();
	void reg();
};