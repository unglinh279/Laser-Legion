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

    levels = {
        {assault()},
        {calvary()},
        {calvary(), vanguard()},
        {warden(), sniper()},
        {assault(), medic()},
        {calvary(), regenerator()},
        {harbinger(), vanguard(), medic()},
        {warden(), assault(), calvary()},
        {harbinger(), calvary(), sentinel(), regenerator()},
        {new Boss("Dr. Cygnus", 40, 12, 6, 6), sniper(), sentinel()},
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

void Game::displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards) {
    cout << '\n' << '\n' << "========================================" << '\n'; 
    cout << player->getName() << '\n';
    cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << '\t' << "Energy: " << player->getCurrentBullet() << "/" << player->getMaxBullet() << '\n';
    if (player->getShield() > 0) cout << "Shield: " << player->getShield() << '\n';
        
    cout << "========================================" << '\n';
    
    for (Enemy* em : enemies) {
        cout << em->getName() << '\n';
        cout << "HP: " << em->getCurrentHealth() << "/" << em->getMaxHealth() << '\n';
        if (em->getType() == "BOSS")
            cout << "Type: BOSS: ?!?" << '\n';
        else
            cout << "Type: " << em->getType() << ": " << em->getAmount() << '\n';
        if (em->getShield() > 0) cout << "Shield: " << em->getShield() << '\n';
        cout << '\n';
    }
    cout << "========================================" << '\n';
    cout << "Cards: " << '\n';
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards[i];
        cout << "(" << i << "): " << std::left << std::setw(18) << card->getName() 
            << card->getType() 
            << "\t for " << card->getAmount() 
            << "\t Cost: " << card->getBulletCost() 
            << '\n';
    }

    cout << "(" << cards.size() << "): End turn" << '\n';
}

bool Game::startRound(Player* player, int roundNumber) {
    cout << "Round: " << roundNumber << '\n';
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    vector<Enemy*> enemies = levels[roundNumber];
    vector<Card*> cards;

    while(true) {
        shuffle(playerDeck.begin(), playerDeck.end(), mt19937{random_device{}()});
        cards.clear();
        for (int i = 0; i < 5; i++) cards.push_back(playerDeck[i]);

        while (true) {
            displayStatus(player, enemies, cards);

            int choice;
            while(true) {
                cout << "Your choice: ";
                cin >> choice;

                if (choice < 0 || choice > cards.size())
                    cout << "Invalid choice! Choose again" << '\n';
                else if (choice != cards.size() && cards[choice]->getBulletCost() > player->getCurrentBullet())
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
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        enemies.erase(enemies.begin() + target);
                    }
                }
                else if (cards[choice]->getType() == "MELEE") {
                    cards[choice]->use(player, enemies[0]);
                    if (enemies[0]->isDead()) {
                        cout << enemies[0]->getName() << " defeated!" << '\n';
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

        cout << player->getName() << " RECHARGE once" << '\n';
        player->reload(1);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void Game::startGame() {
    player = new Player(playerName, 50, 3);

    for (int round = 0; round < levels.size(); round++) {
        if (!startRound(player, round)) {
            cout << "YOU DIED" << '\n';
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout << "GAME OVER" << '\n';
            this_thread::sleep_for(chrono::milliseconds(3000));
            return;
        }


        cout << "CONGRATS!" << '\n';
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "ROUND " << round << " WON!" << '\n';
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "You healed for 5, reload to full, and all shield removed" << '\n';
        this_thread::sleep_for(chrono::milliseconds(2000));

        player->setShield(0);
        player->getHeal(5);
        player->reload(3);

        cout << "You can pick 1 of 4 new cards to add to your deck:" << '\n';
        shuffle(allCards.begin(), allCards.end(), mt19937{random_device{}()});
        for (int i = 0; i < 4; i++) {
            Card* card = allCards[i];
            cout << "(" << i << "): " << std::left << std::setw(20) << card->getName() 
                << card->getType() 
                << "\t for " << card->getAmount() 
                << "\t Cost: " << card->getBulletCost() 
                << '\n';
        }
        int choice;
        while(true) {
            cout << "Your choice: ";
            cin >> choice;

            if (choice < 0 || choice > 3)
                cout << "Invalid choice! Choose again" << '\n';
            else break; 
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Nice! " << allCards[choice]->getName() << " has been added to your deck" << '\n';
        playerDeck.push_back(allCards[choice]);
        allCards.erase(allCards.begin() + choice);
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    cout << "YOU WON THE GAME!" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Here's a cake:" << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << " {\\__/} \n (• . •) \n / >🎂" << '\n';
    this_thread::sleep_for(chrono::milliseconds(5000));
    return;
}