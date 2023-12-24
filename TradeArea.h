#ifndef TRADEAREA_H
#define TRADEAREA_H


#include <list>
#include "CardFactory.h"
#include <sstream>

using namespace std;


class TradeArea {
    list<Card*> tradeCardsList;
public:
    TradeArea() = default;//default constructor
    TradeArea(istream&, CardFactory*);//constructor
    TradeArea& operator+=(Card*);//add a card to trade area
    bool legal(Card*); 
    Card* trade(string); 
    int numCards() const; 
    friend ostream& operator<<(ostream&, TradeArea&); 
    // helpers
    list<Card*>& getTradeCards(); 
    void setTradeCardsList(const list<Card *> &tradeCardsList); 
    int findCardIndex(string name); 
};
#endif
