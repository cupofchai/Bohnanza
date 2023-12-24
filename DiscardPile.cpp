#include "DiscardPile.h"
#include <random>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, DiscardPile& discardPile){
    if (discardPile.pile.empty()) 
        return os;
    auto card = discardPile.pile.back(); //get the last card
    if (card != nullptr) 
        os << *card; //print the card 
    return os; //return the ostream
}

DiscardPile::DiscardPile(istream& is, CardFactory* cardFactory){ // constructor that takes an input stream and a card factory
    string line;  getline(is, line);
    istringstream record(line);
    char cardChar;
    while (record.get(cardChar)) {
        if (cardChar!=' ')
            pile.push_back(cardFactory->getCard(cardChar));
    }
}

DiscardPile& DiscardPile::operator+=(Card* card){ // adds a card to discard pile, returns a reference to the discard pile
    if (card != nullptr)
        pile.push_back(card);
    return *this;
}

Card* DiscardPile::pickUp(){
    if (pile.empty())
        return nullptr;
    Card* card = pile.back();
    pile.pop_back();
    return card;
}

Card* DiscardPile::top() const{
    if (pile.empty())
        return nullptr;
    else return pile.back();
}

void DiscardPile::print(ostream& os){
    for (auto& c : pile) {
        os << c->getName().at(0) << "  ";
    }
}

bool DiscardPile::empty() const {return pile.empty();}
void DiscardPile::pileShuffle() {
    shuffle(pile.begin(), pile.end(), default_random_engine(time(0)));
}
