#include "Game.h"

Enemy* harbinger() {return new Minion("Sonic Harbinger", 30, "ATTACK", 4);}
Enemy* assault() {return new Minion("Assault Trooper", 14, "ATTACK", 5);}
Enemy* calvary() {return new Minion("Arcane Calvary", 10, "ATTACK", 8);}
Enemy* sniper() {return new Minion("Photon Sniper", 6, "ATTACK", 15);}


Enemy* vanguard() {return new Minion("Plasma Vanguard", 14, "SHIELD", 6);}
Enemy* warden() {return new Minion("Chrono Warden", 20, "SHIELD", 4);}
Enemy* sentinel() {return new Minion("Pyro Sentinel", 6, "SHIELD", 14);}

Enemy* medic() {return new Minion("Arcane Siphoner", 12, "HEAL", 6);}
Enemy* regenerator() {return new Minion("Bio-Regenerator", 6, "HEAL", 12);}

Game::Game() = default;
Game::Game(string playerName) {
    this->playerName = playerName;
    round = 1;

    levels = {
        {},
        {assault()},
        {calvary()},
        {calvary(), vanguard()},
        {warden(), sniper()},
        {assault(), medic()},
        {calvary(), regenerator()},
        {harbinger(), vanguard(), medic()},
        {warden(), assault(), calvary()},
        {harbinger(), calvary(), sentinel(), regenerator()},
        {new Boss("Dr. Cygnus", 40, 12, 4, 4), sniper(), sentinel()},
    };

    allCards = {
        new Card("Recharge+", 0, "RECHARGE", 2),
        new Card("Recharge+", 0, "RECHARGE", 2),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Overcharged Blast", 3, "ATTACK", 30),

        new Card("Double Slash", 0, "MELEE", 10),
        new Card("Double Slash", 0, "MELEE", 10),

        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Force Field", 2, "SHIELD", 10),
        new Card("Force Field", 2, "SHIELD", 10),

        new Card("Repair", 1, "HEAL", 6),
        new Card("Heavy Repair", 2, "HEAL", 10),
        new Card("Reconstruction", 3, "HEAL", 20),
    };

    playerDeck = {
        new Card("Recharge", 0, "RECHARGE", 1),
        new Card("Recharge", 0, "RECHARGE", 1),

        new Card("Slash", 0, "MELEE", 6),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Photon Blast", 1, "ATTACK", 8),

        new Card("Repair", 1, "HEAL", 6),

        new Card("Barrier",  1, "SHIELD", 6),
    };
}

void Game::printTutorial() {
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

    std::cout << "Press any key to continue..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Game::getInputInRange(int a, int b) {
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

void Game::checkSave(const string& filename) {
    std::ifstream file(filename);

    if (!file.good()) return;

    std::cout << "Previous save file found." << std::endl;
    std::cout << "(0) Start over" << std::endl;
    std::cout << "(1) View save file" << std::endl;
    std::cout << "(2) Load save file" << std::endl;

    std::cout << "Enter your choice: ";
    int choice = getInputInRange(0, 2);

    if (choice == 0) {
        // Start over
        std::cout << "Starting a new game... \n" << std::endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        return;
    } 
    else if (choice == 1) {
        // View save file
        std::cout << '\n';
        std::ifstream saveFile("GameSave.txt");
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
        checkSave(filename);
    }
    else if (choice == 2) {
        // Load save file
        std::cout << "Loading the save file... \n" << std::endl;
        loadGame(filename);
        return;
    }
    std::cout << '\n';
}
void Game::saveGame(const string& filename) {
    ofstream file(filename);

    this_thread::sleep_for(chrono::milliseconds(2000));
    if (file.is_open()) {
        file << "Player Name: " << playerName << '\n' << '\n';

        file << "Round: " << round+1 << '\n' << '\n';

        file << "All Cards: " << '\n';
        for (const auto& card : allCards)
            file << "\"" << card->getName() << "\"" << ' ' << card->getBulletCost() << ' ' << card->getType() << ' ' << card->getAmount() << '\n';

        file << '\n';

        file << "Player Deck: " << '\n';
        for (const auto& card : playerDeck)
            file << "\"" << card->getName() << "\"" << ' ' << card->getBulletCost() << ' ' << card->getType() << ' ' << card->getAmount() << '\n';
        
        file << '\n';

        file << "Player HP: " << player->getCurrentHealth() << '\n';

        file.close();
        std::cout << "Game saved successfully!" << '\n';
    }
    else {
        std::cout << "Error: Unable to open file" << '\n';
    }
}
void Game::loadGame(const string& filename) {
    allCards.clear();
    playerDeck.clear();

    ifstream file(filename);

    this_thread::sleep_for(chrono::milliseconds(2000));

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Player Name: ") != string::npos) {
                playerName = line.substr(12);
            }
            else if (line.find("Round: ") != string::npos) {
                string roundStr = line.substr(7);
                round = stoi(roundStr);
            }
            else if (line == "All Cards: ") {
                while (getline(file, line) && !line.empty()) {
                    istringstream iss(line);
                    string name, type;
                    int cost, amount;
                    iss >> quoted(name) >> cost >> type >> amount;
                    allCards.push_back(new Card(name, cost, type, amount));
                }
            }
            else if (line == "Player Deck: ") {
                while (getline(file, line) && !line.empty()) {
                    istringstream iss(line);
                    string name, type;
                    int cost, amount;
                    iss >> quoted(name) >> cost >> type >> amount;
                    playerDeck.push_back(new Card(name, cost, type, amount));
                }
            }
            else if (line == "Player HP: ") {
                string hpStr = line.substr(11);
                int HP = stoi(hpStr);
                player->setCurrentHealth(HP);
            }
        }
        
        file.close();
        std::cout << "Game loaded successfully! \n\n";
    }
    else {
        std::cout << "Error: Unable to open file \n\n";
    }
}

void Game::displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards) {
    std::cout << '\n' << '\n' << "========================================" << '\n'; 
    std::cout << player->getName() << '\n';
    std::cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << '\t' << "Energy: " << player->getCurrentBullet() << "/" << player->getMaxBullet() << '\n';
    if (player->getShield() > 0) std::cout << "Shield: " << player->getShield() << '\n';
        
    std::cout << "========================================" << '\n';
    
    for (Enemy* em : enemies) {
        std::cout << em->getName() << '\n';
        std::cout << "HP: " << em->getCurrentHealth() << "/" << em->getMaxHealth() << '\n';
        if (em->getType() == "BOSS")
            std::cout << "Type: BOSS: ?!?" << '\n';
        else
            std::cout << "Type: " << em->getType() << ": " << em->getAmount() << '\n';
        if (em->getShield() > 0) std::cout << "Shield: " << em->getShield() << '\n';
        std::cout << '\n';
    }
    std::cout << "========================================" << '\n';
    std::cout << "Cards: " << '\n';
    for (int i = 0; i < cards.size(); i++) {
        std::cout << "(" << i << "): " << *cards[i] << '\n';
    }

    std::cout << "(" << cards.size() << "): End turn" << '\n';
}

bool Game::startRound(Player* player, int roundNumber) {
    std::cout << "Round: " << roundNumber << '\n';
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    vector<Enemy*> enemies = levels[roundNumber];
    vector<Card*> cards;

    while(true) {
        shuffle(playerDeck.begin(), playerDeck.end(), mt19937{random_device{}()});
        cards.clear();
        for (int i = 0; i < 4; i++) cards.push_back(playerDeck[i]);

        while (true) {
            displayStatus(player, enemies, cards);

            int choice = cards.size();
            while (true) {
                std::cout << "Choose card to play: \n";
                choice = getInputInRange(0, (int)cards.size());
                if (choice != cards.size() && cards[choice]->getBulletCost() > player->getCurrentBullet())
                    std::cout << "Not enough Energy Orbs!\n";
                else break;
            }

            if (choice == cards.size()) break;
            else {
                std::cout << '\n';

                if (cards[choice]->getType() == "ATTACK") {
                    std::cout << "Choose target: \n";
                    int target = getInputInRange(0, enemies.size()-1);

                    cards[choice]->use(player, enemies[target]);
                    if (enemies[target]->isDead()) {
                        std::cout << enemies[target]->getName() << " defeated!" << '\n';
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        enemies.erase(enemies.begin() + target);
                    }
                }
                else if (cards[choice]->getType() == "MELEE") {
                    cards[choice]->use(player, enemies[0]);
                    if (enemies[0]->isDead()) {
                        std::cout << enemies[0]->getName() << " defeated!" << '\n';
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        enemies.erase(enemies.begin());
                    }                
                }
                else {
                    cards[choice]->use(player, player);
                }

                cards.erase(cards.begin() + choice);
            }

            if (enemies.empty()) return true;
            this_thread::sleep_for(chrono::milliseconds(2000));
        }

        for (Enemy* em : enemies) {
            if (em->getType() == "ATTACK" || em->getType() == "BOSS")
                em->useAbility(player);
            else em->useAbility(enemies[0]);
            if (player->isDead()) return false;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        this_thread::sleep_for(chrono::milliseconds(1000));

        std::cout << player->getName() << " RECHARGE once" << '\n';
        player->reload(1);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void Game::startGame() {
    player = new Player(playerName, 50, 3);

    printTutorial();

    checkSave("GameSave.txt");

    for (; round < levels.size(); round++) {
        if (!startRound(player, round)) {
            std::cout << "YOU DIED" << '\n';
            this_thread::sleep_for(chrono::milliseconds(1000));
            std::cout << "GAME OVER" << '\n';
            this_thread::sleep_for(chrono::milliseconds(3000));
            return;
        }

        std::cout << " \nCONGRATS! \n";
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << "ROUND " << round << " WON!" << '\n';
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << '\n' << "You healed for 5, reload to full, and all shield removed" << '\n';
        this_thread::sleep_for(chrono::milliseconds(2000));

        player->setShield(0);
        player->getHeal(5);
        player->reload(3);

        std::cout << '\n' << "You can pick 1 of 4 new cards to add to your deck:" << '\n';
        shuffle(allCards.begin(), allCards.end(), mt19937{random_device{}()});
        for (int i = 0; i < 4; i++) 
            std::cout << "(" << i << "): " << *allCards[i] << '\n';

        int choice = getInputInRange(0, 3);
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << "Nice! " << allCards[choice]->getName() << " has been added to your deck \n\n";
        playerDeck.push_back(allCards[choice]);
        allCards.erase(allCards.begin() + choice);
        this_thread::sleep_for(chrono::milliseconds(2000));

        std::cout << "Do you want to save current game state? (Y/N)";
        std::string saveInput;

        while (true) {
            getline(std::cin, saveInput);

            if (saveInput.length() == 1 && (saveInput[0] == 'Y' || saveInput[0] == 'N')) {
                if (saveInput[0] == 'Y') {
                    saveGame("GameSave.txt");
                    break;
                }
                else if (saveInput[0] == 'N') break;
            }

            std::cout << "Invalid input. Please enter 'Y' or 'N' \n";
        }
    }

    std::cout << "YOU WON THE GAME!" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    std::cout << "Here's a cake:" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    std::cout << " {\\__/} \n (• . •) \n / >🎂" << '\n';
    this_thread::sleep_for(chrono::milliseconds(5000));
    return;
}