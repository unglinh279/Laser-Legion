#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    int maxBullet;
    int currentBullet;
    int isCrit;
public:
    Player();
    Player(string name, int maxHealth, int maxBullet);

    int getMaxBullet();
    int getCurrentBullet();
    void reload(int amount);
    void setCurrentBullet(int bullet);
};

#endif