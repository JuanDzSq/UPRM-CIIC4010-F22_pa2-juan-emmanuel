#include "Fighting.h"

Fighting::Fighting(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage): Entity(ox, oy, ow, oh)
{
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;
}

Fighting::~Fighting() {}

void Fighting::fightingDraw()
{
    fightingSprite.draw(fx, fy, fw, fh);
}

