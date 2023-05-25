#include "Boss.h"

Boss::Boss() = default;
Boss::Boss(string name, int maxHealth, int attack, int shield, int heal) {
    this->name = name;
    this->maxHealth = maxHealth;
    stat = new int[3];
    stat[0] = attack; stat[1] = shield; stat[2] = heal;
}

void Boss::useAbility(Character* target) {
    cout << name << " attack " << target->getName() << " for " << stat[0] << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << name << " shield itself for " << stat[1] << '\n';
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << name << " heal itself for " << stat[2] << '\n';

    target->takeDamage(stat[0]);
    this->getShield(stat[1]);
    this->getHeal(stat[2]);
}

