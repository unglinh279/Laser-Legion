#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
private:
    int attack;
    int shield;
    int heal;
public:
    Boss();
    Boss(string name, int maxHealth, int attack, int shield, int heal);

    void useAbility(Character* target) override;

    string getType() override {
        return "BOSS";
    }
    int getAmount() override {
        return 0;
    }
};

#endif