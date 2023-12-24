#include "CardFactory.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

CardFactory::CardFactory(){
    //create the deck of cards, fill it with default cards
    for (size_t numBlue = 0; numBlue < 20; ++numBlue) {deck.push_back(new Blue());}
    for (size_t numChili = 0; numChili < 18; ++numChili) {deck.push_back(new Chili());}
    for (size_t numStink = 0; numStink < 16; ++numStink) {deck.push_back(new Stink());}
    for (size_t numGreen = 0; numGreen < 14; ++numGreen) {deck.push_back(new Green());}
    for (size_t numSoy = 0; numSoy < 12; ++numSoy) {deck.push_back(new Soy());}
    for (size_t numBlack = 0; numBlack < 10; ++numBlack) {deck.push_back(new Black());}
    for (size_t numRed = 0; numRed < 8; ++numRed) {deck.push_back(new Red());}
    for (size_t numGarden = 0; numGarden < 6; ++numGarden) {deck.push_back(new Garden());}
    used.reserve(104);
}

Deck CardFactory::getDeck(){
    shuffle(deck.begin(), deck.end(), default_random_engine(time(0)));
    return deck;
}

Card* CardFactory::getCard(const char& cardChar){
    Card* card = nullptr; //create a pointer to a card, set it to null, so we can return it if we don't find the card
    for (int i = 0; i < 104; ++i) {
        if (deck[i]->getName()[0] == cardChar) {
            card = deck[i]; deck.erase(deck.begin() + i);
            this->used.addCard(card); //add the card to the outDeck
            deck.erase(deck.begin() + i); //remove the card from the deck
            break;
        }
    }
    return card;
}

CardFactory::~CardFactory() { //delete all the cards in the deck
    for (auto &card : deck)
        delete card;
}

CardFactory* CardFactory::getCardFactory() { //returns the singleton instance of CardFactory
    static CardFactory cFactory;
    return &cFactory;
}