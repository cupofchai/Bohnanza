#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include "CardFactory.h"
#include <vector>

using namespace std;

class DiscardPile {
private:
    vector<Card*> pile;
public:
    DiscardPile() = default; // default constructor
    DiscardPile(istream&, CardFactory*); // constructor that takes an input stream and a card factory
    DiscardPile& operator+=(Card*);// add a card to the discard pile, returns a reference to the discard pile
    Card* pickUp();// removes top card from discard pile and returns it
    Card* top() const;// return top card from discard pile
    void print(ostream&);
    friend ostream& operator<<(ostream&, DiscardPile&);

    //helper
    bool empty() const; // is empty method
    void pileShuffle(); //  ensures cards are in random order
};

#endif