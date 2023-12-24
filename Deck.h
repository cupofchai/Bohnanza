#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class Deck : public vector<Card*> { 
public:
    Deck() = default;
    Deck(istream&, class CardFactory*); //constructor for load game
    Card* draw(); //draws a card returns nullptr if deck is empty
    friend ostream& operator<<(ostream&, Deck&); 

    //helper
    void addCard(Card*); //adds a card to the deck
};

#endif