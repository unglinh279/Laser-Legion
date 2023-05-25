#include "System.h"

void System::printTutorial() {
    std::cout << "Title: Laser Legion: Turn-Based Strategy Card Game Tutorial\n\n";

    std::cout << "Introduction:\n";
    std::cout << "Welcome to Laser Legion, a thrilling sci-fi, robotic-themed, turn-based strategy card game. Your mission is to defeat multiple enemies across 10 stages and face a challenging boss fight at the end. In this tutorial, we'll guide you through the game mechanics, card types, combat system, and strategies to help you emerge victorious.\n\n";

    std::cout << "Game Objective:\n";
    std::cout << "Defeat all enemies in each stage using a combination of strategic card plays and resource management. Survive through all 10 stages and overcome the final boss to claim victory.\n\n";

    std::cout << "Game Mechanics:\n\n";
    std::cout << "Card Types:\n";
    std::cout << "a. Recharge Card: Use this card to gain additional orbs (maximum of 3) to spend on other cards.\n";
    std::cout << "b. Attack Card: Deal damage to the enemy. Each attack card has a specific bullet cost and damage value.\n";
    std::cout << "c. Heal Card: Restore your health. Heal cards affect the first enemy in the battle.\n";
    std::cout << "d. Shield Card: Defend against enemy attacks. Shield cards also affect the first enemy.\n\n";

    std::cout << "Energy Orbs:\n";
    std::cout << "a. At the start of each fight, you have 3 orbs available to spend.\n";
    std::cout << "b. Each card has a bullet cost. Spend orbs to use the cards you've drawn.\n";
    std::cout << "c. You recharge 1 orbs each turn\n";
    std::cout << "d. Using a Recharge card replenishes 1 energy orbs.\n\n";

    std::cout << "Turn Structure:\n";
    std::cout << "a. Each fight begins with your turn. Draw 4 random cards from your deck.\n";
    std::cout << "b. Spend orbs to play cards and execute their effects. Alternatively, you can play a Reload card to replenish your bullets.\n";
    std::cout << "c. You can end your turn at any time once you've played the desired cards.\n\n";

    std::cout << "Enemy Abilities:\n";
    std::cout << "a. After your turn, each enemy performs their ability.\n";
    std::cout << "b. Enemies have two types of abilities:\n";
    std::cout << "   i. Attack: Deals damage to you.\n";
    std::cout << "   ii. Heal/Shield: Affects the first enemy, either healing or shielding them.\n";

    std::cout << "Press Enter to continue..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int System::getInputInRange(int a, int b) {
    int userInput;
    std::string inputString;

    while (true) {
        std::cout << "Enter an integer from " << a << " to " << b << ": ";
        std::getline(std::cin, inputString);

        // Use stringstream to convert input to integer
        std::stringstream ss(inputString);

        if (ss >> userInput && ss.eof()) {
            // Check if the integer is within the specified range
            if (userInput >= a && userInput <= b) {
                return userInput; // Return valid input
            }
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }
}