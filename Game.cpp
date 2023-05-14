#include "Game.h"

Game::Game() = default;
Game::Game(string playerName) {
    this->playerName = playerName;

    levels = {
        {new Minion("SpiderBot", 20, "ATTACK", 4)},
        {new Minion("SpiderBot", 20, "ATTACK", 4), new Minion("DroneBot", 10, "ATTACK", 8)}
    };

    allCards = {
        new Card("Recharge", 0, "RELOAD", 1),
        new Card("Recharge", 0, "RELOAD", 1),
        new Card("Recharge+", 0, "RELOAD", 2),
        new Card("Recharge+", 0, "RELOAD", 2),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Overcharged Blast", 3, "ATTACK", 30),

        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Force Field", 2, "SHIELD", 15),
        new Card("Force Field", 2, "SHIELD", 15),

        new Card("Repair", 1, "HEAL", 6),
        new Card("Repair", 1, "HEAL", 6),
        new Card("Heavy Repair", 2, "HEAL", 15),
        new Card("Heavy Repair", 2, "HEAL", 15),
    };

    playerDeck = {
        new Card("Recharge", 0, "RELOAD", 1),
        new Card("Recharge", 0, "RELOAD", 1),
        new Card("Recharge", 0, "RELOAD", 1),

        new Card("Melee", 0, "MELEE", 6),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Photon Blast", 1, "ATTACK", 8),

        new Card("Repair", 1, "HEAL", 6),

        new Card("Barrier",  1, "SHIELD", 6)
    };
}

void Game::displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards) {
    cout << '\n' << '\n' << "========================================" << '\n'; 
    cout << player->getName() << '\n';
    cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << '\t' << "Energy: " << player->getCurrentBullet() << "/" << player->getMaxBullet() << '\n';
    if (player->getShield() > 0) cout << "Shield: " << player->getShield() << '\n';
        
    cout << "========================================" << '\n';
    
    for (Enemy* em : enemies) {
        cout << em->getName() << '\n';
        cout << "HP: " << em->getCurrentHealth() << "/" << em->getMaxHealth() << "\nType: " << em->getType() << ": " << em->getAmount() << '\n';
        if (em->getShield() > 0) cout << "Shield: " << em->getShield() << '\n';
    }
    cout << "========================================" << '\n';
    cout << "Cards: " << '\n';
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards[i];
        cout << "(" << i << "): " << std::left << std::setw(15) << card->getName() 
            << card->getType() 
            << "\t for " << card->getAmount() 
            << "\t Cost: " << card->getBulletCost() 
            << '\n';
    }

    cout << "(" << cards.size() << "): End turn" << '\n';
}

bool Game::startRound(Player* player, int roundNumber) {
    cout << "Round: " << roundNumber << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    vector<Enemy*> enemies = levels[roundNumber];
    vector<Card*> cards;

    while(true) {
        shuffle(playerDeck.begin(), playerDeck.end(), mt19937{random_device{}()});
        cards.clear();
        for (int i = 0; i < 4; i++) cards.push_back(playerDeck[i]);

        while (true) {
            displayStatus(player, enemies, cards);

            int choice;
            while(true) {
                cout << "Your choice: ";
                cin >> choice;

                if (choice < 0 || choice > cards.size())
                    cout << "Invalid choice! Choose again" << '\n';
                if (choice != cards.size() && cards[choice]->getBulletCost() > player->getCurrentBullet())
                    cout << "Not enough Energy Orbs! Choose again" << '\n';
                else break; 
            }

            if (choice == cards.size()) break;
            else {
                cout << '\n';

                if (cards[choice]->getType() == "ATTACK") {
                    int target;
                    while(true) {
                        cout << "Choose target (0" << " - " << enemies.size()-1 << "): ";
                        cin >> target;

                        if (target < 0 || target > enemies.size())
                            cout << "Invalid target! Choose again";
                        else break; 
                    }
                    cards[choice]->use(player, enemies[target]);
                    if (enemies[target]->isDead()) {
                        cout << enemies[target]->getName() << " defeated!" << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        enemies.erase(enemies.begin() + target);
                    }
                }
                else if (cards[choice]->getType() == "MELEE") {
                    cards[choice]->use(player, enemies[0]);
                    if (enemies[0]->isDead()) {
                        cout << enemies[0]->getName() << " defeated!" << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        enemies.erase(enemies.begin());
                    }                
                }
                else {
                    cards[choice]->use(player, player);
                }

                cards.erase(cards.begin() + choice);
            }

            if (enemies.empty()) return true;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

        for (Enemy* em : enemies) {
            if (em->getType() == "ATTACK")
                em->useAbility(player);
            else em->useAbility(enemies[0]);
            if (player->isDead()) return false;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Game::startGame() {
    player = new Player(playerName, 50, 3);

    for (int round = 0; round < levels.size(); round++) {
        if (startRound(player, round)) {
            cout << "CONGRATS!" << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "ROUND " << round << " WON!" << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
        else {
            cout << "YOU DIED" << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "GAME OVER" << '\n';
            return;
        }

        player->getHeal(10);
        player->reload();
    }

    cout << "YOU WON THE GAME!" << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "Here's a cake:" << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "{\\__/} \n ( • . •) \n / >🎂" << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return;
}