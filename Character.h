#ifndef CHARACTER_H
#define CHARACTER_H

#include<bits/stdc++.h>

using namespace std;

class Character {
protected:
    string name;
    int maxHealth;
    int currentHealth;
    int shield;
public:
    Character();
    Character(string name, int maxHealth);

    void takeDamage(int amount);
    void getHeal(int amount);
    void getShield(int amount);

    bool isDead();

    string getName();
    int getMaxHealth();
    int getCurrentHealth();
    int getShield();
};

#endif