#include "Boss.h"

Boss::Boss() = default;
Boss::Boss(string name, int maxHealth, int attack, int shield, int heal) : Enemy(name, maxHealth), attack(attack), shield(shield), heal(heal) {};

void Boss::useAbility(Character* target) {
    cout << name << " attack " << target->getName() << " for " << attack << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << name << " shield itself for " << shield << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << name << " heal itself for " << heal << '\n';

    target->takeDamage(attack);
    this->getShield(shield);
    this->getHeal(heal);
}

