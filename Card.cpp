#include "Card.h"

using namespace std;

Card::Card()
{
	this->value = rand() % 13 + 1;
	this->suit = rand() % 4 + 1;
	strcpy_s(this->serialNum, strlen("Default") + 1, "Default");
}

Card::Card(const int suit, const int value, const char* serialNum)
{
	this->suit = suit;
	this->value = value;
	strcpy_s(this->serialNum, strlen(serialNum) + 1, serialNum);
}

Card& Card::operator=(const Card& other)
{
	if (this != &other)
	{
		this->setSuit(other.suit);
		this->setValue(other.value);
		this->setSerialNum(other.serialNum);
	}

	return *this;
}

void Card::setSuit(const char suit)
{
	this->suit = suit;
}

void Card::setValue(const char value)
{
	this->value = value;
}

void Card::setSerialNum(const char* serialNum)
{
	strcpy_s(this->serialNum, strlen(serialNum) + 1, serialNum);
}

void Card::printSuit() const
{
	switch (this->suit)
	{
	case 1:
		cout << "CLUBS"; break;
	case 2:
		cout << "DIAMONDS"; break;
	case 3:
		cout << "HEARTS"; break;
	case 4:
		cout << "SPADES"; break;
	default:
		break;
	}
}

void Card::printValue() const
{
	switch (this->value)
	{
	case 1:
		cout << "A"; break;
	case 11:
		cout << "J"; break;
	case 12:
		cout << "Q"; break;
	case 13:
		cout << "K"; break;
	default:
		cout << this->value; break;
	}
}

void Card::printCard() const
{
	cout << "| ";
	this->printValue();
	cout << " ("; this->printSuit(); cout << ") |" << endl;
}

int Card::getSuit() const
{
	return this->suit;
}

int Card::getValue() const
{
	return this->value;
}

const char* Card::getSerialNum() const
{
	return this->serialNum;
}


