#include<bits/stdc++.h>

#include "Game.h"
#include "System.h"

const string SAVEFILE = "GameSave.txt";

using namespace std;

int main() {
    System system;

    system.printTutorial();
    while (true) {
        std::ifstream file(SAVEFILE);

        if (!file.good()) {
            // Start Over
            std::cout << "Starting a new game... \n" << std::endl;
            this_thread::sleep_for(chrono::milliseconds(2000));

            Game game;
            game.setNewPlayer();
            game.startGame();
            break;
        }

        std::cout << "Previous save file found." << std::endl;
        std::cout << "(0) Start over" << std::endl;
        std::cout << "(1) View save file" << std::endl;
        std::cout << "(2) Load save file" << std::endl;

        std::cout << "Enter your choice: ";
        int choice = system.getInputInRange(0, 2);

        if (choice == 0) {
            // Start Over
            std::cout << "Starting a new game... \n" << std::endl;
            this_thread::sleep_for(chrono::milliseconds(2000));

            Game game;
            game.setNewPlayer();
            game.startGame();
            break;
        } 
        else if (choice == 1) {
            // View save file
            std::cout << '\n';
            std::ifstream saveFile(SAVEFILE);
            if (saveFile.is_open()) {
                std::string line;
                bool printLine = true;
                while (std::getline(saveFile, line)) {
                    if (line == "All Cards: ") {
                        // Skip printing the "All Cards" section
                        printLine = false;
                    }
                    if (printLine) {
                        std::cout << line << std::endl;
                    }
                    if (line.empty()) {
                        // Reset the flag after printing an empty line
                        printLine = true;
                    }
                }
                saveFile.close();
            } 
            else std::cout << "Error: Unable to open the save file." << std::endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            std::cout << '\n';

            // recur...
        }
        else if (choice == 2) {
            // Load save file
            std::cout << "Loading the save file... \n" << std::endl;
            this_thread::sleep_for(chrono::milliseconds(2000));

            Game game;
            game.loadGame(SAVEFILE);
            game.startGame();
            break;
        }
        std::cout << '\n';
    }

    std::cout << "YOU WON THE GAME!" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    std::cout << "Here's a cake:" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    std::cout << " {\\__/} \n (• . •) \n / >🎂" << '\n';
    this_thread::sleep_for(chrono::milliseconds(5000));
    return 0;
}