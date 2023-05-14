#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    Enemy(string name, int maxHealth);

    virtual void useAbility(Character* target) = 0;
    virtual string getType() = 0;
    virtual int getAmount() = 0;
};

#endif