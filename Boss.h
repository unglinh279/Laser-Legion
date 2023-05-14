#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
private:
public:
    Boss();
    Boss(string name, int maxHealth);
};

#endif