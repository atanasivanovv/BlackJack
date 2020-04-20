#pragma once
#include "Card.h"

class Deck {
private:
	Card* cards;
	char seriesNum[10];
	size_t size, capacity;
	size_t countCards = size;

	void copy(const Deck& other)
	{
		if (this->capacity <= other.capacity)
			capacity *= 2;

		this->cards = new Card[this->capacity];
		
		for (size_t i = 0; i < this->size; i++)
		{
			this->cards[i] = other.cards[i];
		}

		this->size = other.size;
	}

	void erase()
	{
		delete[] this->cards;
	}

	void resize()
	{
		this->capacity *= 2;
		Card* buffer = new Card[this->capacity];

		for (int i = 0; i < this->size; i++)
		{
			buffer[i] = this->cards[i];
		}

		this->erase();
		this->cards = buffer;
	}

	void fillDeck()
	{
		int i = 0;
		for (int suit = 1; suit <= 4; suit++)
		{
			for (int val = 1; val <= 13; val++)
			{
				this->cards[i] = Card(suit, val, "Default");
				++i;
			}
		}
	}

	void shuffle(const int numOfCards)
	{
		for (int i = 0; i < numOfCards; i++)
		{
			int random = rand() % numOfCards;

			// Swap with random one
			Card temp = this->cards[i];
			this->cards[i] = this->cards[random];
			this->cards[random] = temp;
		}
	}

public:
	Deck();
	Deck(const int numOfCards);
	Deck(const Deck& other);
	Deck operator=(const Deck& other);
	~Deck();


	void draw();
	void swap(int num1, int num2);
	size_t suit_count(int suit);
	size_t rank_count(int value);

	void print() const;
	Card getDrawnCard() const;
	double getSize();
};