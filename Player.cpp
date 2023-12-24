#include "Player.h"
#include "Card.h"
#include "CardFactory.h"
#include "Chain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Player::Player(istream& is, CardFactory* cardFactory){
    string line;
    getline(is, line);
    istringstream reader(line);
    int nameSize = 0;
    while (reader.get() != ':')
        ++nameSize; 
    reader.seekg(0); 
    string tempString(nameSize, '\0'); 
    reader.read(&tempString[0], nameSize + 1); 
    name = tempString; 
    string coin;  reader >> coin;
    numCoins = stoi(coin); 
    
    for (int i = 0; i < 3; ++i) {
        char cardChar;
        for (int i = 0; i < 2; ++i)
            is.get(cardChar); 
        if (cardChar == 'B') {chains[i] = new Chain<Blue>(is, cardFactory);}
        else if (cardChar == 'C') {chains[i] = new Chain<Chili>(is, cardFactory);}
        else if (cardChar == 'S') {chains[i] = new Chain<Stink>(is, cardFactory);}
        else if (cardChar == 'G') {chains[i] = new Chain<Green>(is, cardFactory);}
        else if (cardChar == 's') {chains[i] = new Chain<Soy>(is, cardFactory);}
        else if (cardChar == 'b') {chains[i] = new Chain<Black>(is, cardFactory);}
        else if (cardChar == 'R') {chains[i] = new Chain<Red>(is, cardFactory);}
        else if (cardChar == 'g') {chains[i] = new Chain<Garden>(is, cardFactory);}
        if (i == 2) 
            isThereThirdChain = true; 
        if (cardChar == '(') { 
            chains[i] = new Chain_Base();
            if (is.get() == 'e') { 
                if (i == 2) 
                    isThereThirdChain = true;
                else 
                    isThereThirdChain = false;
            }
            else 
                isThereThirdChain = false;
            getline(is, line);  
        }
    }
    hand = new Hand(is, cardFactory);
}

string Player::getName() const{return name;}

int Player::getNumCoins() const{return numCoins;}

Player& Player::operator+=(int coins){
    numCoins += coins;
    return *this;
}

int Player::getMaxNumChains() const {
    if (isThereThirdChain)
        return 3;
    return 2;
}

int Player::getNumChains() const{
    int size = 0;
    for (auto &card : chains) {
        if (!card->empty())
            ++size;
    }
    return size;
}

Chain_Base& Player::operator[](int i){
    if (i >= getMaxNumChains())
        throw exception();
    else
        return *(chains[i]);
}

void Player::buyThirdChain(){
    if (numCoins < 3)
        throw exception();
    numCoins -= 3;
    isThereThirdChain = true;
}

void Player::printHand(ostream& os, bool printAll){
    if (hand->top() == nullptr) {
        os << "You do not have enough cards!\n";
        return;
    }
    if (!printAll)
        hand->top()->print(os);
    else
        os << *hand;
}

void Player::startNewChain(int i, const char& cardChar){
    delete chains[i]; //delete the old chain
    if (cardChar == 'B') {chains[i] = new Chain<Blue>();}
    else if (cardChar == 'C') {chains[i] = new Chain<Chili>();}
    else if (cardChar == 'S') {chains[i] = new Chain<Stink>();}
    else if (cardChar == 'G') {chains[i] = new Chain<Green>();}
    else if (cardChar == 's') {chains[i] = new Chain<Soy>();}
    else if (cardChar == 'b') {chains[i] = new Chain<Black>();}
    else if (cardChar == 'R') {chains[i] = new Chain<Red>();}
    else if (cardChar == 'g') {chains[i] = new Chain<Garden>();}
    else chains[i] = new Chain_Base();
}

Hand* Player::getHand(){return hand;
}

Player::~Player(){ //destructor
    for (auto& chainPtr : chains)   //delete all chains
        delete chainPtr;
    delete hand; //delete hand
}

ostream& operator<<(ostream& os, Player& player){ 
    os << player.name << ": " << player.numCoins << " coins" << endl; //print the name and number of coins
    for (int i = 0; i < 3; ++i) { //print out all the chains
        if (i==2 && !player.isThereThirdChain)
            os << "-(there isn't a third chain)" << endl;
        else
            os << "-" << *(player.chains[i]) << endl;
    }
    return os;
}



void Player::addCard(Card* card){hand->addCard(card);}

void Player::addCoins(int coins){numCoins += coins;}

void Player::removeCoins(int coins){numCoins -= coins;}


void Player::removeChain(Chain_Base* chain){
    for (int i = 0; i < 3; ++i) {
        if (chains[i] == chain) {
            delete chains[i];
            chains[i] = new Chain_Base();
        }
    }
}

void Player::addChain(Chain_Base* chain){
    for (int i = 0; i < 3; ++i) {
        if (chains[i]->empty()) {
            delete chains[i];
            chains[i] = chain;
            return;
        }
    }
}

void Player::removeChain(int i){
    delete chains[i];
    chains[i] = new Chain_Base();
}