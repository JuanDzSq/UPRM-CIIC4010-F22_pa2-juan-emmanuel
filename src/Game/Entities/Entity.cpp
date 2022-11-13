#include "Entity.h"

Entity::Entity(int ox, int oy, int ow, int oh)
{
    this->ox = ox;
    this->oy = oy;
    this->oh = oh;
    this->ow = ow;
    // this->fx = fx;
    // this->fy = fy;
    // this->fh = fh;
    // this->fw = fw;
    // this->health = health;
    // this->baseDamage = baseDamage;
}

Entity::~Entity() {}

Fighting::Fighting(int fx, int fy, int fw, int fh, int health, int baseDamage)
{
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;
}

Fighting::~Fighting() {}

void Entity::inOverworldDraw()
{
    overworldSprite.draw(ox, oy, ow, oh);
}

void Fighting::fightingDraw()
{
    fightingSprite.draw(fx, fy, fw, fh);
}

bool Entity::collides(Entity *entity)
{
    return this->getBounds().intersects(entity->getBounds());
}

ofRectangle Entity::getBounds()
{
    return ofRectangle(ox, oy, ow, oh);
}

ofRectangle Entity::getBounds(int x, int y)
{
    return ofRectangle(x, y, ow, oh);
}
