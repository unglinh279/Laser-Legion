#ifndef CARD_H
#define CARD_H

#include<bits/stdc++.h>
#include "Character.h"
#include "Player.h"
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
};

#endif