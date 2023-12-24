#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <iostream>
#include <string>
#include <array>

using namespace std;

class Table { 
    Player* player1;
    Player* player2;
    Deck* deck; 
    DiscardPile* discardPile; 
    TradeArea* tradeArea; 
public:
    Table(string, string); // Constructor
    Table(istream&, CardFactory*); // load game constructor
    ~Table();// Destructor
    bool win(string&) const; 
    void print(ostream&);
    friend ostream& operator<<(ostream&, Table&); 

    //helpers
    Player* getPlayer1();
    Player* getPlayer2();
    void setPlayers(array<Player*, 2> players);
    Deck* getDeck();
    void setDeck(Deck* deck);
    DiscardPile* getDiscardPile();
    void setDiscardPile(DiscardPile* discardPile);
    TradeArea* getTradeArea();
    void setTradeArea(TradeArea* tradeArea);
};

#endif