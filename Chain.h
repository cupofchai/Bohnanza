#ifndef CHAIN_H
#define CHAIN_H

#include "CardFactory.h"
#include <vector>
#include <sstream>

using namespace std;

class Chain_Base {
protected:
    virtual void printChain(ostream& os) const { os << "!the Chain is empty"; } //to be overridden in the derived classes
public:
    Chain_Base() = default; //default constructor
    virtual ~Chain_Base() = default; 
    virtual Chain_Base& operator+=(Card*) { return *this; } 
    virtual int sell() { return 0; } 
    virtual bool empty() const { return true; } 
    virtual Card* removeCard() { return nullptr; } 

    friend ostream& operator<<(ostream& os, const Chain_Base& cb) { 
        cb.printChain(os);
        return os;
    }
};

template<typename T>
class Chain: public Chain_Base {
    vector<T*> cards;
protected:
    virtual void printChain(ostream& os) const override; //prints all cards in the chain
public:
    Chain() = default;
    Chain(istream&, CardFactory*);
    Chain_Base& operator+=(Card*) override; //adds a card to the chain and returns a reference to the chain
    int sell() override; //Returns the number of coins using getCardsPerCoin()
    friend ostream& operator<<(ostream& os, Chain<T>& chain)//prints the chain using the insertion operator
    {
        chain.printChain(os);
        return os;
    }

    //helpers
    T* getCard(int index) { return cards[index]; } //returns card at given index
    bool empty() const override { return cards.empty(); } //checks if chain is empty
    Card* removeCard() override; //removes the top card from the chain
    int size() { return cards.size(); } //returns size of the chain
};

template<typename T>
void Chain<T>::printChain(ostream& os) const
{
    Card* topCard = dynamic_cast<Card*>(cards.front());
    os << topCard->getName() << " ";
    for (auto card : cards) {card->print(os);}
}


template<typename T>
Chain<T>::Chain(istream& is, CardFactory* factory)
{
    //move the indicator to the next line
    string line;
    getline(is, line);
    istringstream chainLine(line);
    char ch;
    while (chainLine.get(ch)) {
        T* card = dynamic_cast<T*>(factory->getCard(ch));
        if (card && ch != ' ')  cards.push_back(card);
    }
}


template<typename T>
Chain_Base& Chain<T>::operator+=(Card* card)
{
    T* newCard = dynamic_cast<T*>(card);
    if (newCard) cards.push_back(newCard);
    else throw IllegalType();
    return *this;
}


template<typename T>
int Chain<T>::sell()
{
    int numCards = cards.size();
    // If chain is empty, simply return 0
    if (cards.empty()) return 0;
    else {
        int coins= 1; //coins to be returned
        Card* topCard = dynamic_cast<Card*>(cards.front());
        if (numCards < topCard->getCardsPerCoin(coins))
            return 0;
        while (numCards > topCard->getCardsPerCoin(coins)) {
            if (numCards >= topCard->getCardsPerCoin(coins + 1))
                ++coins;
            else break;
        }
        return coins;
    }
}

template<typename T>
Card* Chain<T>::removeCard()
{
    if (cards.empty()) return nullptr;
    else {
        Card* card = cards.back();
        cards.pop_back();
        return card;
    }
}
#endif
