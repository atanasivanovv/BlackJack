#include "Player.h"

Player::Player()
{
	strcpy_s(this->name, strlen("Default") + 1, "Default");
	this->age = 0;
	this->wins = 0;
	this->winOdd = 0;
	this->currentPoints = 0;
	this->playerValidation = false;
	this->gamesPlayed = 0;
}

Player::Player(const char* name, int age, int wins, double winOdd, int currentPoints)
{
	strcpy_s(this->name, strlen(name) + 1, name);
	this->age = age;
	this->wins = wins;
	this->winOdd = winOdd;
	this->currentPoints = currentPoints;
	this->playerValidation = false;
	this->gamesPlayed = 0;
}

bool Player::getPlayerValidation() const
{
	return this->playerValidation;
}

void Player::setDrawnCard(const Card drawnCard)
{
	this->drawnCard = drawnCard;
}

Card Player::getDrawnCard() const
{
	return this->drawnCard;
}

void Player::setCurrentPoints(int points)
{
	this->currentPoints = points;
}

void Player::addPoints(const Card card)
{
	switch (card.getValue())
	{
	case 1:
		this->currentPoints += 11;
		break;
	case 2:
		this->currentPoints += 2;
		break;
	case 3:
		this->currentPoints += 3;
		break;
	case 4:
		this->currentPoints += 4;
		break;
	case 5:
		this->currentPoints += 5;
		break;
	case 6:
		this->currentPoints += 6;
		break;
	case 7:
		this->currentPoints += 7;
		break;
	case 8:
		this->currentPoints += 8;
		break;
	case 9:
		this->currentPoints += 9;
		break;
	case 10: case 11: case 12: case 13:
		this->currentPoints += 10;
		break;
	default:
		break;
	}
}

int Player::getCurrentPoints() const
{
	return this->currentPoints;
}

void Player::addWin()
{
	this->wins++;
}

void Player::addGamePlayed()
{
	this->gamesPlayed++;
}

int Player::getGamesPlayed() const
{
	return this->gamesPlayed;
}

void Player::updateWinOdd()
{
	this->winOdd = this->wins / this->gamesPlayed;
}

int Player::getWinOdd() const
{
	return this->winOdd;
}


void Player::print()
{
	cout << "   Name: " << this->name << endl;
	cout << "   Age: " << this->age << endl;
	cout << "   Wins: " << this->wins << endl;
	cout << "   Win Odd: " << this->winOdd * 100 << "%" << endl;
	cout << "   Current Points: " << this->currentPoints << endl;
}

void Player::printStats()
{
	cout << "   Wins: " << this->wins << endl;
	cout << "   Win Odd: " << this->winOdd * 100 << "%" << endl;
}

void Player::getName()
{
	cout << this->name << endl;
}

void Player::reg()
{
	cout << "   Enter your name: ";

	cin.getline(this->name, 64);

	while (!this->validation())
	{
		cout << "   Enter a correct name!" << endl;
		cout << "   Enter your name: ";
	}

	cout << "   Enter your age: ";
	cin >> this->age;
	cout << endl;

	if (this->age >= 18 && this->age <= 100)
	{
		cout << "   NEW PLAYER CREATED..." << endl;
		this->print();
		this->playerValidation = true;

		cout << endl;
		cout << "   ------------------    THE GAME IS STARTING...    ------------------   " << endl;
	}
	else {
		cout << "   You are under age or you entered a wrong input! You cannot play this game." << endl;
		this->age = 0;

		cout << endl;
		cout << "   ------------------    QUITTING THE GAME...    ------------------   " << endl;
	}


}
