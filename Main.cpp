#include <string>
#include <iostream>
#include "Table.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Card.h"
#include <vector>

using namespace std;

int main() {
    
    string player1Name, player2Name;
    Table table(player1Name, player2Name);

    //Does the player want to load the game
    cout << "Do you want to resume your previous game? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        string filename;
        cout << "Enter the name of the file where your game is saved: ";
        cin >> filename;
        ifstream ldfile(filename);
        if (ldfile) {
            // Reconstructing table from file
            table.~Table(); // deleting prev table
            new (&table) Table(ldfile, CardFactory::getCardFactory());
            cout << "> Saved game has been loaded.\n\n";
        }  else {
            // If no saved game exists, start a new game
            cout << "> No saved game was found. Let's start a new game! \n\n";
            goto newGame;
        }
    } else {
        newGame:
        //players
        cout << "Enter the name of player 1: ";
        cin >> player1Name;
        cout << "Enter the name of player 2: ";
        cin >> player2Name;

        //create the table
        table.~Table();
        new (&table) Table(player1Name, player2Name);
        //get player1 
        Player* player1 = table.getPlayer1();
        //get player2 
        Player* player2 = table.getPlayer2();

        for (auto i = 0; i < 5; ++i) {
            *(player1->getHand()) += (table.getDeck()->draw());
            *(player2->getHand()) += (table.getDeck()->draw());
        }
        cout << "\nEach player has 5 cards\n";
    }

    string winner; //name of the winner player
    Player* player1 = table.getPlayer1(); //get player1
    Player* player2 = table.getPlayer2(); //get player2 
    TradeArea* tradeArea = table.getTradeArea();  // trade area 
    DiscardPile* discardPile = table.getDiscardPile();  // discard pile 
    Deck* deck = table.getDeck();   // Deck 

    while (!deck->empty()) { 
        cout << "Do you want to pause and save the game? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            string filename;
            cout << "Enter the name of the file: ";
            cin >> filename;
            ofstream out(filename);
            table.print(out);//save the game
            out.close();
            cout<<"Game saved successfully!";
            exit(0); // end the game
        }
        //vector of pointers to the players
        vector<Player*> players;
        players.push_back(player1);
        players.push_back(player2);

        for (auto& player : players) { //start round
            cout << table << endl; //print table
            cout << "> Player: " << player->getName() << "'s turn.\n";
            if (player->getMaxNumChains() == 2) {
                try {
                    string answer;
                    cout << "Do you want to purchase a third chain? (y/n): ";
                    cin >> answer;

                    if (answer == "y") {
                        if (player->getNumCoins() < 3) {
                            throw NotEnoughCoins();  // Throw the custom exception
                        } else {
                            player->buyThirdChain();
                            cout << "You have purchased a third chain!\n";
                        }
                    }
                } catch (const NotEnoughCoins& e) {
                    cout << "Error: " << e.what() << endl;
                }
            }

            *(player->getHand()) += (deck->draw()); //draw a card from deck
            cout << "\n" << " You drew a card from the deck. \n";

            // if there are cards in trade area
            if (tradeArea->numCards()) {

                string answer;
                cout << "Do you want to add the cards in the trade area to your chains? (y/n): \n";
                cin >> answer;
                while (!(answer == "y" || answer == "n")) {
                    do {
                        cout << "Invalid answer! Please enter 'y' or 'n':  ";
                        cin >> answer;
                    } while (!(answer == "y" || answer == "n"));
                }

                vector<string> tradingCards; //vector of cards to be traded
                for (auto& card : tradeArea->getTradeCards()) { //get cards from trade area
                    tradingCards.push_back(card->getName()); //add cards to vector
                }

                if (answer == "y") {
                    for (string& tradingCard : tradingCards) {
                        Card* tradeCard = tradeArea->trade(tradingCard);
                        bool canChain = false;

                        for (auto i = 0; i < player->getMaxNumChains(); ++i) {
                            if ((*player)[i].empty()) player->startNewChain(i, tradingCard[0]);

                            try {
                                (*player)[i] += tradeCard;
                                canChain = true;
                                cout << "* Card: " << tradingCard << " successfully chained to chain " << i << "!\n";
                                break;  // Exit the loop if the card is successfully chained
                            } catch (const IllegalType& e) {
                            cout << "Error: " << e.showMessage() << " Card: " << tradingCard << " doesn't match chain " << i << ".\n";
                            }
                        }

                        if (!canChain) {
                            cout << "* Card: " << tradingCard << " doesn't match any of your chains, and will be discarded.\n";
                            (*discardPile) += tradeCard;  // or handle the card in a discard pile
                        }
                    }

                    cout << "+ Now you have the following chains: \n";
                    // Print the chains after the turn

                
                    for (int i = 0; i < player->getMaxNumChains(); ++i) {
                        cout << "  [" << i << "]" << (*player)[i] << endl;
                    }
                    cout << endl;
                }
                // if answer is no
                else {
                    // transfer all cards in trade area to discard pile
                    for (auto& tc : tradingCards) {
                        (*discardPile) += tradeArea->trade(tc);
                    }
                    cout << "+ All the cards in the trade area have been discarded.\n\n";
                }
            }

            // Let player play the topmost card from Hand, and ask if wanting to repeat once
            
            bool repeat;
            int numRepeat = 1;

            do {
                cout << "You played the topmost card from your hand.\n";
                player->printHand(cout, false);
                cout << "\n";

                // Play top most card from hand
                if (player->getHand()->top()) {
                    Card* playedCard = player->getHand()->play();
                    bool canChain = false;

                    // Check if played card can be added to any of the chain
                    for (int i = 0; i < player->getMaxNumChains(); ++i) {
                        if ((*player)[i].empty()) {
                            player->startNewChain(i, playedCard->getName()[0]);
                        }

                        try {
                            (*player)[i] += playedCard;
                            canChain = true;
                            cout << "+ You have added the card to an existing chain!\n";
                            break;
                        } catch (const IllegalType&) {
                            // If card type doesn't match chain type, check next chain
                            continue;
                        }
                    }

                    // If no matching chain found
                    if (!canChain) {
                        string answer;
                        cout << "None of your chains match the card you played:(\n";

                        int index;
                        // Keep asking for index until it gets a valid one
                        while (true) {
                            cout << "Please enter the index of the chain you want to sell: ";
                            cin >> answer;

                            try {
                                index = stoi(answer);
                                break;  // Exit the loop if stoi succeeds
                            } catch (const exception&) {
                                cout << "Please enter a valid index.\n";
                            }
                        }

                        int earnedCoin = 0;
                        bool validIndex = false;

                        while (!validIndex) {
                            try {
                                earnedCoin = (*player)[index].sell();

                                // Put all cards in chain into discard pile and shuffle discard pile
                                while (!(*player)[index].empty()) {
                                    (*discardPile) += (*player)[index].removeCard();
                                }
                                discardPile->pileShuffle();

                                // Start a new chain with the given card type
                                player->startNewChain(index, playedCard->getName()[0]);
                                (*player)[index] += playedCard;

                                // Increase player coins
                                (*player) += earnedCoin;

                                cout << "* You sold your chain and earned " << earnedCoin << " coins!\n";
                                validIndex = true;
                            } catch (const IllegalType& e) {
                                cout << "Error: " << e.showMessage() << endl;
                                cout << "Please re-enter a valid index: ";
                                cin >> index;
                            }
                        }

                        cout << "+ You have played your top card: " << playedCard->getName() << endl;
                    }
                } else {
                    cout << "You got no cards in hand\n";
                }

                // Print the chains the player currently owns
                cout << "> Your Chains: \n";
                for (int i = 0; i < player->getMaxNumChains(); ++i) {
                    cout << "  [" << i << "]" << (*player)[i] << endl;
                }

                // Topmost card in hand
                cout << "> Now the top card on your hand: ";
                player->printHand(cout, false);
                cout << "\n\n";

                // Ask if player wants to play topmost card again
                repeat = false;
                if (numRepeat) {
                    string answer;
                    cout << "Do you want to play your top card again? (y/n) ";
                    cin >> answer;
                    if (answer == "y") {
                        repeat = true;
                        --numRepeat;
                    }
                }
            } while (repeat);



            // Ask if player decides to show his full hand and select an arbitrary card
            string answer;
            cout << "Do you want to show your full hand and discard an arbitrary card? (y/n): ";
            cin >> answer;
            while (!(answer == "y" || answer == "n")) {
                do {
                    cout << "Invalid answer! Please enter (y/n):  ";
                    cin >> answer;
                } while (!(answer == "y" || answer == "n"));
            }

            if (answer == "y") {
                // show player's full hand 
                cout << "Your hand:" << player->getName() << endl;
                player->printHand(cout, true);
                cout << endl;

                // player chooses card to discard
                Card* discarded = nullptr;
                cout << "Enter the index of the card you want to discard: ";
    
                // loop to get valid index
                int index;
                bool validIndex = false;

                while (!validIndex) {
                try {
                        cin >> index;
                        // Check if the index is valid (within the range of the hand size)
                        if (index >= 0 && index < player->getHand()->size()) {
                            validIndex = true;  // Exit the loop if the index is valid
                        } else {
                            cout << "Please enter a valid index: ";
                        }
                } catch (exception&) {
                    cout << "Please enter a valid index: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            try {
                discarded = (*(player->getHand()))[index];
            } catch (exception) {
                cout << "> Error" << endl;
                cout << "> Please re-enter a valid index." << endl;
                // The loop will handle asking for a valid index again.
            }

            // Then place the card on the discard pile
            (*discardPile) += discarded;
            cout << "> You have discarded: " << discarded->getName() << ". \n";
        }

            // draw 3 cards from deck and place them in trade area
            for (int i = 0; i < 3; ++i)  (*tradeArea) += (deck->draw());
            cout << "\n" << "> 3 cards have been placed into the trade area.\n\n";

            // While top card of discard pile matches a card in trade area
            while (tradeArea->legal(discardPile->top())) {
                // remove top card from discard pile and put it in trade area
                Card* topDiscarded = discardPile->pickUp();
                (*tradeArea) += topDiscarded;
                cout << topDiscarded->getName();
                cout << " has been added to the trade area.\n\n";
            }

            // for all cards in the trade area, ask the player if they want to add the card to a chain
            if (tradeArea->numCards()) {
                do {
                    string answer;
                    cout << "\n> Trade area : " << *tradeArea;
                    cout << "\n> Please enter the character of the card you'd like to add to a chain, if you don't want to add any, type 'n': ";
                    input_answer:
                    cin >> answer;
                    if (answer == "n") break;
                    else {  
                        Card* card = nullptr;
                        if (answer[0] == 'B') card = tradeArea->trade("Blue");
                        else if (answer[0] == 'C') card = tradeArea->trade("Chili");
                        else if (answer[0] == 'S') card = tradeArea->trade("Stink");
                        else if (answer[0] == 'G') card = tradeArea->trade("Green");
                        else if (answer[0] == 's') card = tradeArea->trade("Soy");
                        else if (answer[0] == 'b') card = tradeArea->trade("Black");
                        else if (answer[0] == 'R') card = tradeArea->trade("Red");
                        else if (answer[0] == 'g') card = tradeArea->trade("Garden");
                        else {
                            cout << "Please enter a valid character: ";
                            goto input_answer;
                        }
                        if (!card) {
                            cout << "Please enter your choice again: ";
                            goto input_answer;
                        }
                        else {
                            // check if the chosen card can be added to any chain
                            bool chainFlag = false;
                            for (int i = 0; i < player->getMaxNumChains(); ++i) {
                                if ((*player)[i].empty())   player->startNewChain(i, card->getName()[0]);
                                try {
                                    (*player)[i] += card;
                                    chainFlag = true;
                                    cout << "+ You have added the card to a new chain: " << card->getName() << "\n";
                                    cout << "+ Your chains are: \n";
                                    for (int j = 0; j < player->getMaxNumChains(); ++j) {
                                        cout << "  [" << j << "]" << (*player)[j] << endl;
                                    }
                                    break;
                                } catch (...) {
                                    cout << "An unexpected error occurred while adding the card to a chain.\n";
                                }


                            }
                            // if no chain has the same type as the card played
                            if (!chainFlag) {
                                cout << "This card doesn't match any of your chains:(\n";
                                cout << "Enter the index of the chain you want to sell:  ";
                                
                                int index;
                                askIndex3:
                                try {
                                    index = stoi(answer);  // May throw invalid_argument exception
                                }
                                catch (exception&) {
                                    cout << "Please enter a valid index:  ";
                                    cin >> answer;
                                    goto askIndex3;
                                }
                                startNewChain2:
                                try {
                                    int earnedCoin = (*player)[index].sell(); 
                                    // Put all cards in the chain into discard pile and shuffle discard pile
                                    while (!(*player)[index].empty()) {
                                        (*discardPile) += (*player)[index].removeCard();
                                    }
                                    discardPile->pileShuffle();
                                    // Start a new chain with the given card type
                                    player->startNewChain(index, card->getName()[0]);
                                    (*player)[index] += card;
                                    // increase player coins
                                    (*player) += earnedCoin;
                                    cout << "* You sold your chain and earned ";
                                    cout << earnedCoin << " coins!\n";
                                }
                                catch (const IllegalType& e) {
                                    cout << "Error: " << e.showMessage() << " Please re-enter a valid index.\n";
                                    goto askIndex3;
                                }
                            
                                cout << "You played your topmost card: " << card->getName() << endl;
                            }
                            else {
                                cout << "+ You have added the card to a new chain: " << card->getName() << "\n";
                                cout << "+ Your chains are: " << endl;
                            }
                            for (int i = 0; i < player->getMaxNumChains(); ++i) {
                                cout << "  '" << i << "'" << (*player)[i] << endl;
                            }
                        }
                    }
                } while (tradeArea->numCards());
                
            }

            // Player draws 2 cards from deck
            for (int i=0;i<2;++i)  *(player->getHand()) += (deck->draw());
            cout << "Player has finished his turn. 2 Cards were drawn\n\n";
        }
    }

    cout << "\n\nGAME OVER" << endl;
    if (winner == "No one") {  // If 2 players have same number of coins
        cout << "It's a draw!" << endl;
    } else {
        cout << "Player: " << winner << " wins!" << endl;
    }
    return 0;
}