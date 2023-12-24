#ifndef HAND_H
#define HAND_H

#include <vector>
#include <list>
#include <queue>
#include <memory>
#include <exception>
#include "CardFactory.h"

using namespace std;

class Hand {
    queue<Card*> handCards;
public:
    Hand() = default;
    Hand(istream&, CardFactory*); // constructor
    Hand& operator+=(Card*); // add card to hand
    Card* play(); // play card
    Card* top() const; // return top card
    Card* operator[](int); // return card at index
    friend ostream& operator<<(ostream&, Hand&); // print hand

    //helpers
    const queue<Card *> &getHandCards() const;
    void setHandCards(const queue<Card *> &handCards);
    bool isEmpty() const;
    void addCard(Card* card);
    Card* removeCard();
    Card* getCard(int index);
    void printHand();
    void removeCard(Card* card);
    void removeCard(int index);
    int size();
};

#endif