#include "Table.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Table::Table(string player1Name, string player2Name){ // Constructor
    
    // players
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    
    // deck
    deck = new Deck(CardFactory::getCardFactory()->getDeck());
    
    // discard pile
    tradeArea = new TradeArea();
    
    // trade area
    discardPile = new DiscardPile();
}

Table::Table(istream& is, CardFactory* cardFactory){ // load game constructor
    string line;
    player1 = new Player(is, cardFactory); 
    player2 = new Player(is, cardFactory); 
    getline(is, line);  
    deck = new Deck(is, cardFactory);
    getline(is, line);  
    tradeArea = new TradeArea(is, cardFactory);
    getline(is, line);   
    discardPile = new DiscardPile(is, cardFactory);
}

bool Table::win(string& name) const
{
    if (deck->empty()) {
        if (player1->getNumCoins() > player2->getNumCoins())
            name = player1->getName();
        else if (player1->getNumCoins() < player2->getNumCoins())
            name = player2->getName();
        else
            name = "Draw";
        return true;
    }
    return false;
}

Player* Table::getPlayer1() {return player1;}
Player* Table::getPlayer2() {return player2;}
Deck* Table::getDeck() {return deck;}
TradeArea* Table::getTradeArea(){return tradeArea;}
DiscardPile* Table::getDiscardPile(){return discardPile;}

void Table::print(ostream& os){
    os << *player1 << "Hand: ";  player1->printHand(os, true);  os << endl;
    os << *player2 << "Hand: ";  player2->printHand(os, true);  os << endl;
    os << "Deck:" << endl << *deck << endl;
    os << "Trade Area:" << endl << *tradeArea << endl;
    os << "Discard Pile:" << endl;  discardPile->print(os);
}

ostream& operator<<(ostream& os, Table& table){
    os << "Table:";
    os << *(table.player1) << endl;
    os << *(table.player2) << endl;
    os << "Trade area: " << *(table.tradeArea) << endl;
    os << "Discard Pile: " << *(table.discardPile) << endl;
    os << "Deck: " << *(table.deck) << endl;
    os << "End of Table" << endl;
    return os;
}

Table::~Table() { // Destructor
    delete player1;
    delete player2;
    delete deck;
    delete tradeArea;
    delete discardPile;
}