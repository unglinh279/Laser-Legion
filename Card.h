#ifndef CARD_H
#define CARD_H

#include<bits/stdc++.h>
#include "Characters/Character.h"
#include "Characters/Player.h"
using namespace std;

class Card {
private:
    string name;
    string type;
    int amount;
    int bulletCost;
public:
    Card();
    Card(string name, int bulletCost, string type, int amount);
    void use(Player* player, Character* target);

    string getName();
    string getType();
    int getAmount();
    int getBulletCost();

    friend ostream& operator <<(ostream& os, const Card& card) {
        os << std::left << std::setw(25) 
        << card.name << card.type
        << "\t for " << card.amount 
        << "\t Cost: " << card.bulletCost;
        return os;
    }
};

#endif