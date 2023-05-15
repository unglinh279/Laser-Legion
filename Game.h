#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Minion.h"
#include "Character.h"
#include "Card.h"
#include "Boss.h"
#include<bits/stdc++.h>

using namespace std;

class Game {
private:
    string playerName;
    vector<vector<Enemy*> > levels;

    vector<Card*> allCards;
    vector<Card*> playerDeck;

    Player* player;

    void displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards);

public:
    Game();
    Game(string playerName);

    bool startRound(Player* player, int roundNumber);
    void startGame();
};

#endif