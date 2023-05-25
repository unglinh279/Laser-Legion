#include "Minion.h"

Minion::Minion() = default;
Minion::Minion(string name, int maxHealth, string type, int amount) : Enemy(name, maxHealth), type(type), amount(amount) {};

void Minion::useAbility(Character* target) {
    cout << name << " " << type << " " << target->getName() << " for " << amount << '\n';

    if (type == "ATTACK") {
        target->takeDamage(amount);
    }
    else if (type == "SHIELD") {
        target->getShield(amount);
    }
    else if (type == "HEAL") {
        target->getHeal(amount);
    }
}

string Minion::getType() {
    return type;
}
int Minion::getAmount() {
    return amount;
}