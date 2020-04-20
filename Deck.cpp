#include "Deck.h"

Deck::Deck()
{
	this->size = 52;
	this->capacity = 408;
	this->cards = new Card[this->capacity];

	// Fill the feck and shuffle the cards so it has all 52 with no duplicates
	this->fillDeck();
	this->shuffle(this->size);

	strcpy_s(this->seriesNum, strlen("Default") + 1, "Default");
	this->countCards = this->size;
}

Deck::Deck(const int numOfCards)
{
	this->capacity = 104;
	this->resize();
	this->size = numOfCards;

	if (numOfCards < 52)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			this->cards[i] = Card();
		}
	}
	else
	{
		this->fillDeck();
		for (size_t i = 52; i < this->size; i++)
		{
			this->cards[i] = Card();
		}
	}
	
	strcpy_s(this->seriesNum, strlen("Custom") + 1, "Custom");
	this->countCards = this->size;
}


Deck::Deck(const Deck& other)
{
	this->copy(other);
}

Deck Deck::operator=(const Deck& other)
{
	this->resize();

	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}

	return *this;
}

Deck::~Deck()
{
	this->erase();
}


void Deck::draw()
{
	Card* smaller = new Card[this->size + 1];
	this->cards[this->size] = this->cards[0];
	Card drawnCard = this->cards[this->size];

	for (int i = 0; i < this->size; i++)
	{
		smaller[i] = this->cards[i + 1];
	}

	this->erase();
	this->cards = smaller;
	this->countCards--;
}

void Deck::swap(int num1, int num2)
{
	Card temp = this->cards[num1 - 1];
	this->cards[num1 - 1] = this->cards[num2 - 1];
	this->cards[num2 - 1] = temp;
}

size_t Deck::suit_count(int suit)
{
	size_t counter = 0;
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->cards[i].getSuit() == suit)
			counter++;
	}

	return counter;
}

size_t Deck::rank_count(int value)
{
	size_t counter = 0;
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->cards[i].getValue() == value)
			counter++;
	}

	return counter;
}

void Deck::print() const
{
	for (int i = 0; i < this->size; i++)
	{
		this->cards[i].printCard();
	}
}

Card Deck::getDrawnCard() const
{
	return this->cards[0];
}

double Deck::getSize() 
{
	return this->countCards;
}
