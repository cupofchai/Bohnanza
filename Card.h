#pragma once
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Card {
public:
    Card() = default; // default constructor
    virtual ~Card() = default; // virtual destructor
    Card(const Card&) = delete; // copy constructor
    Card& operator=(const Card&) = delete; // copy assignment operator

    virtual int getCardsPerCoin(int coins) = 0; // returns the number of cards needed to earn the associated number of coins
    virtual string getName() const = 0; // returns the name of the card
    friend ostream& operator<<(ostream& os, Card& card); // friend function to print the card
    virtual void print(ostream& out) = 0; // prints the card
};

class Blue : public Card {
    friend class CardFactory; // giving CardFactory access to the constructor
private:
    Blue(); // private constructor
public:
    int getCardsPerCoin(int coins) override; 
    string getName() const override; 
    void print(ostream& out) override; 
};


class Chili : public Card {
    friend class CardFactory;
private:
    Chili();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Stink : public Card {
    friend class CardFactory;
private:
    Stink();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Green : public Card {
    friend class CardFactory;
private:
    Green();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Soy : public Card {
    friend class CardFactory;
private:
    Soy();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Black : public Card {
    friend class CardFactory;
private:
    Black();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Red : public Card {
    friend class CardFactory;
private:
    Red();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class Garden : public Card {
    friend class CardFactory;
private:
    Garden();
public:
    int getCardsPerCoin(int coins) override;
    string getName() const override;
    void print(ostream& out) override;
};

class IllegalType : private exception { // exception class for illegal type of card being added to an incompatible chain
public:
    string showMessage() const {
        return "The type of card does not match this chain.";
    }; // returns the error message
};
class NotEnoughCoins : public exception {  // player has less than 3 coins so can't purchase 3rd chain
public:
    const char* what() const noexcept override {
        return "Not enough coins to purchase a third chain.";
    }
};
#endif