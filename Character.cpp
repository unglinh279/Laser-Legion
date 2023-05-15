#include "Character.h"

Character::Character() = default;
Character::Character(string name, int maxHealth) : name(name), maxHealth(maxHealth), currentHealth(maxHealth), shield(0) {};

void Character::takeDamage(int amount) {
    int shieldReduct = min(amount, shield);

    shield -= shieldReduct;
    amount -= shieldReduct;

    currentHealth -= amount;
}
void Character::getHeal(int amount) {
    currentHealth += amount;
    currentHealth = min(currentHealth, maxHealth);
}
void Character::getShield(int amount) {
    shield += amount;
}

bool Character::isDead() {
    return currentHealth <= 0;
}

string Character::getName() {
    return name;
}
int Character::getMaxHealth() {
    return maxHealth;
}
int Character::getCurrentHealth() {
    return currentHealth;
}
int Character::getShield() {
    return shield;
}

void Character::setShield(int shield) {
    this->shield = shield;
}