#pragma once

#include "ofMain.h"
#include "Entity.h"

class Fighting: public Entity
{
protected:
    int health;
    int baseDamage;
    int fx, fy, fw, fh; // Fighting coordinates and dimensions
    ofImage fightingSprite;

public:
    Fighting(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage);
    virtual ~Fighting();
    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();
    ofRectangle getBounds();
    ofRectangle getBounds(int ox, int oy);
    int getHealth() { return health; };
    void setHealth(int health) { this->health = health; };
    int getDmg() { return baseDamage; };
    void setDmg(int baseDamage) { this->baseDamage = baseDamage; };
};