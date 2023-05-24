#ifndef GAME_H
#define GAME_H

#include "Characters/Player.h"
#include "Characters/Enemy.h"
#include "Characters/Minion.h"
#include "Characters/Character.h"
#include "Card.h"
#include "Characters/Boss.h"
#include<bits/stdc++.h>

using namespace std;

class Game {
private:
    int round;
    string playerName;
    vector<vector<Enemy*> > levels;

    vector<Card*> allCards;
    vector<Card*> playerDeck;

    Player* player;

    void printTutorial();
    int getInputInRange(int a, int b);
    bool startRound(Player* player, int roundNumber);
    void displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards);
public:
    Game();
    Game(string playerName);

    void checkSave(const string& filename);
    void saveGame(const string& filename);
    void loadGame(const string& filename);
    void startGame();
};

#endif