#pragma once
#include <iostream>
#include <random>
#include "time.h"

enum class Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {
private:
	int suit;
	int value;
	char serialNum[15];
public:
	Card();
	Card(const int suit, const int value, const char* serialNum);
	Card& operator=(const Card& other);

	void printSuit() const;
	void printValue() const;
	int getSuit() const;
	int getValue() const;
	void printCard() const;
	const char* getSerialNum() const;

	void setSuit(const char suit);
	void setValue(const char value);
	void setSerialNum(const char* serialNum);
};