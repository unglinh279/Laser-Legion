#include<bits/stdc++.h>

#include "Game.h"

using namespace std;

int main() {
    string playerName;

    while (true) {
        std::cout << "Welcome! Enter a name (less than 13 characters): ";
        std::getline(std::cin, playerName);
        
        if (playerName.length() < 13) {
            break;
        }
        
        std::cout << "Invalid input! Please enter a name less than 13 characters." << std::endl;
    }
    
    Game game(playerName);
    game.startGame();

    return 0;
}