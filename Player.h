#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Chain.h"
#include "Hand.h"

using namespace std;

class Player {
private:
    string name;
    int numCoins;
    int maxNumChains;
    Hand* hand;
    int numChains = 3;
    array<Chain_Base*, 3> chains{
        {new Chain_Base(), new Chain_Base(), new Chain_Base() }};
    bool isThereThirdChain = false;
public:
    Player(const std::string name) : name(name) {hand = new Hand();}
    Player(std::istream&, CardFactory*);
    ~Player();
    std::string getName() const;
    int getNumCoins() const;
    Player& operator+=(int);
    int getMaxNumChains() const;
    int getNumChains() const;
    Chain_Base& operator[](int i);
    void buyThirdChain();
    void printHand(std::ostream&, bool);
    friend std::ostream& operator<<(std::ostream&, Player&);

    //helpers
    void startNewChain(int, const char&);
    Hand* getHand();
    void addCard(Card*);
    void addCoins(int);
    void removeCoins(int);
    void removeCard(Card*);
    void removeCard(int);
    void addChain(Chain_Base*);
    void removeChain(Chain_Base*);
    void removeChain(int);
};

#endif