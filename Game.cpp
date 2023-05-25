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

Game::Game() {
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

void Game::setNewPlayer() {
    string playerName;

    while (true) {
        std::cout << "Enter player name (less than 13 characters): ";
        std::getline(std::cin, playerName);
        
        if (playerName.length() < 13) {
            player = new Player(playerName, 50, 3);
            return;
        }
        
        std::cout << "Invalid input! Please enter a name less than 13 characters." << std::endl;
    }
}

void Game::saveGame(const string& filename) {
    ofstream file(filename);
    std::cout << "\n Saving...\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
    if (file.is_open()) {
        file << "Player Name: " << player->getName() << '\n' << '\n';

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

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Player Name: ") != string::npos) {
                string playerName = line.substr(13);
                player = new Player(playerName, 50, 3);
            }
            else if (line.find("Round: ") != string::npos) {
                string roundStr = line.substr(7);
                int r = stoi(roundStr);
                this->round = r;
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

bool Game::startRound(Player* player) {
    std::cout << "Round: " << round << '\n';
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    vector<Enemy*> enemies = levels[round];
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
                choice = system.getInputInRange(0, (int)cards.size());
                if (choice != cards.size() && cards[choice]->getBulletCost() > player->getCurrentBullet())
                    std::cout << "Not enough Energy Orbs!\n";
                else break;
                std::cout << '\n';
            }

            if (choice == cards.size()) break;
            else {
                std::cout << '\n';

                if (cards[choice]->getType() == "ATTACK") {
                    std::cout << "Choose target: \n";
                    int target = system.getInputInRange(0, enemies.size()-1);

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
        std::cout << '\n';
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
    for (; round < levels.size(); round++) {
        if (!startRound(player)) {
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

        int choice = system.getInputInRange(0, 3);
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << "Nice! " << allCards[choice]->getName() << " has been added to your deck \n\n";
        playerDeck.push_back(allCards[choice]);
        allCards.erase(allCards.begin() + choice);
        this_thread::sleep_for(chrono::milliseconds(2000));

        std::cout << "Do you want to save current game state? (Y/N)";
        std::string saveInput;

        while (true) {
            getline(std::cin, saveInput);
            saveInput[0] = tolower(saveInput[0]);
            if (saveInput.length() == 1 && (saveInput[0] == 'y' || saveInput[0] == 'n')) {
                if (saveInput[0] == 'y') {
                    saveGame(SAVEFILE);
                    break;
                }
                else if (saveInput[0] == 'n') break;
            }

            std::cout << "Invalid input. Please enter 'y' or 'n' \n";
        }
        cout << '\n';
    }
    return;
}