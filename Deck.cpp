#include "Deck.h"
#include "CardFactory.h"
#include <algorithm>
#include <sstream>

using namespace std;


Deck::Deck(istream &in, CardFactory *cardFactory) { //constructor for load game
    Deck deck;
    string line;	getline(in, line);
    istringstream record(line);
    char cardChar;
    while (record.get(cardChar)) {
        if (cardChar != ' ')
            deck.push_back(cardFactory->getCard(cardChar));
    }
    new (&(*this)) Deck(deck);
}

Card* Deck::draw() { //draws a card and returns nullptr if deck is empty
    if (empty())
        return nullptr;
    Card* card = this->back();
    this->pop_back();
    return card;
}

ostream& operator<<(ostream& os, Deck& deck) { 
    for (auto& card : deck) {os << *card;}
    return os;
}

void Deck::addCard(Card* card) { //adds a card to the deck
    this->push_back(card);
}

