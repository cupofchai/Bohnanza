#include "Card.h"
using namespace std;



//constructors
Red::Red() {}
Blue::Blue() {}
Green::Green() {}
Stink::Stink() {}
Chili::Chili() {}
Soy::Soy() {}
Black::Black() {}
Garden::Garden() {}


ostream& operator<<(ostream &os, Card& card){
    card.print(os);
    return os;
}

//Blue
string Blue::getName() const {return "Blue";}
void Blue::print(ostream& out) {out << "B  ";}

//Chili
string Chili::getName() const {return "Chili";}
void Chili::print(ostream& out) {out << "C  ";}

//Green
string Stink::getName() const {return "Stink";}
void Stink::print(ostream& out) {out << "S  ";}

//Green
string Green::getName() const {return "Green";}
void Green::print(ostream& out) {out << "G  ";}

//Soy
string Soy::getName() const {return "Soy";}
void Soy::print(ostream& out) {out << "s  ";}

//Black
string Black::getName() const {return "Black";}
void Black::print(ostream& out) {out << "b  ";}

//Red
string Red::getName() const {return "Red";}
void Red::print(ostream& out) {out << "R  ";}

//garden
string Garden::getName() const {return "Garden";}
void Garden::print(ostream& out) {out << "g  ";}

////////////////////////GetCardsPerCoin 

//Blue
int Blue::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 4;
    } else if (coins == 2) {
        return 6;
    } else if (coins == 3) {
        return 8;
    } else if (coins == 4) {
        return 10;
    } else {
        return 0;
    }
}

//Chili
int Chili::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 6;
    } else if (coins == 3) {
        return 8;
    } else if (coins == 4) {
        return 9;
    } else {
        return 0;
    }
}

//Stink
int Stink::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 5;
    } else if (coins == 3) {
        return 7;
    } else if (coins == 4) {
        return 8;
    } else {
        return 0;
    }
}

//Green
int Green::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 5;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 7;
    } else {
        return 0;
    }
}

//Soy
int Soy::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 4;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 7;
    } else {
        return 0;
    }
}

//Black
int Black::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 4;
    } else if (coins == 3) {
        return 5;
    } else if (coins == 4) {
        return 6;
    } else {
        return 0;
    }
}

//Red
int Red::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 3;
    } else if (coins == 3) {
        return 4;
    } else if (coins == 4) {
        return 5;
    } else {
        return 0;
    }
}

//Garden
int Garden::getCardsPerCoin(int coins)  {
    if (coins == 2) {
        return 2;
    } else if (coins == 3) {
        return 3;
    } else {
        return 0;
    }
}