#include "TradeArea.h"
#include <algorithm>
#include <iterator>

using namespace std;

ostream& operator<<(ostream& os, TradeArea& tradeArea){
    for (auto& card : tradeArea.tradeCardsList) {
        card->print(os);
    }
    return os;
}

TradeArea::TradeArea(istream& is, CardFactory* cardFactory){ //load game constructor
    string line;
    getline(is, line);
    istringstream record(line);
    char cardChar;
    while (record.get(cardChar)) {
        if (cardChar != ' ')
            tradeCardsList.push_back(cardFactory->getCard(cardChar));
    }
}

TradeArea& TradeArea::operator+=(Card* card){ 
    if (card != nullptr)
        tradeCardsList.push_back(card);//add card to trade area
    return *this;//return trade area
}

bool TradeArea::legal(Card* card){
    if (card == nullptr)  
        return false;
    for (auto& xc : tradeCardsList) {
        if ((xc->getName()) == (card->getName())) //if the card is legal
            return true;
    }
    return false;
}

Card* TradeArea::trade(string name){
    auto i = find_if(tradeCardsList.begin(), tradeCardsList.end(), [name](Card* card) { return card->getName() == name; }); //find the card in the trade area
    if (i != tradeCardsList.end()) { 
        Card* card = *i;
        tradeCardsList.erase(i);
        return card;
    }
    throw runtime_error("Card not found in trade area");
}

int TradeArea::findCardIndex(string name) {
    auto iter = find_if(tradeCardsList.begin(), tradeCardsList.end(), [name](Card* card) { return card->getName() == name; });

    if (iter != tradeCardsList.end()) {
        return distance(tradeCardsList.begin(), iter);
    } else {
        return -1;
    }
}

int TradeArea::numCards() const{return tradeCardsList.size();}
list<Card*>& TradeArea::getTradeCards(){return tradeCardsList;}