#include "Player.h"

Player::Player() = default;
Player::Player(string name, int maxHealth, int maxBullet) {
    this->name = name;
    this->maxHealth = maxHealth;
    currentHealth = maxHealth;
    this->maxBullet = maxBullet;
    currentBullet = maxBullet;
}

int Player::getMaxBullet() {
    return maxBullet;
}
int Player::getCurrentBullet() {
    return currentBullet;
}

void Player::reload() {
    currentBullet++;
    currentBullet = min(currentBullet, maxBullet);
}

void Player::setCurrentBullet(int bullet) {
    if (bullet >= 0 && bullet <= maxBullet) currentBullet = bullet;
    else cout << "Error setting bullet!" << '\n';
}