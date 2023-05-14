#include<bits/stdc++.h>

#include "Game.h"

using namespace std;

int main() {
    cout << "Welcome! Enter player name: ";
    string playerName;
    getline(cin, playerName);

    Game game(playerName);
    game.startGame();

    return 0;
}