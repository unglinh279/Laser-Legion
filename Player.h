#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    int maxBullet;
    int currentBullet;
public:
    Player();
    Player(string name, int maxHealth, int maxBullet);

    int getMaxBullet();
    int getCurrentBullet();
    void reload();
    void setCurrentBullet(int bullet);
};

#endif