#ifndef MINION_H
#define MINION_H

#include "Enemy.h"

class Minion : public Enemy {
private:
    int amount; // attack/shield/heal
    string type; // attack/shield/heal
public:
    Minion();
    Minion(string name, int maxHealth, string type, int amount);

    void useAbility(Character* target) override;

    string getType() override;
    int getAmount() override;
};

#endif