#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Minion.h"
#include "Character.h"
#include "Card.h"
#include "Boss.h"
#include "System.h"
#include<bits/stdc++.h>

using namespace std;

class Game {
private:
    const string SAVEFILE = "GameSave.txt";

    System system;
    int round;
    vector<vector<Enemy*> > levels;

    vector<Card*> allCards;
    vector<Card*> playerDeck;

    Player* player;

    bool startRound(Player* player);
    void displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards);
public:
    Game();

    void saveGame(const string& filename);
    void loadGame(const string& filename);
    void startGame();

    void setNewPlayer();
};

#endif