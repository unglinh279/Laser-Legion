#include "Boss.h"

Boss::Boss() = default;
Boss::Boss(string name, int maxHealth) : Enemy(name, maxHealth) {};