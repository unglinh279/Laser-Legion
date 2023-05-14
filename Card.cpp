#include "Card.h"

Card::Card() = default;
Card::Card(string name, int bulletCost, string type, int amount) : name(name), bulletCost(bulletCost), type(type), amount(amount) {};

void Card::use(Player* player, Character* target) {
    cout << player->getName() << " used " << name << " on " << target->getName() << '\n';
    player->setCurrentBullet(player->getCurrentBullet() - bulletCost);

    if (type == "ATTACK" || type == "MELEE") {
        target->takeDamage(amount);
    }
    else if (type == "SHIELD") {
        player->getShield(amount);
    }
    else if (type == "HEAL") {
        player->getHeal(amount);
    }
    else if (type == "RELOAD") {
        player->reload();
    }
}

int Card::getAmount() {
    return amount;
}
int Card::getBulletCost() {
    return bulletCost;
}
string Card::getName() {
    return name;
}
string Card::getType() {
    return type;
}