#pragma once

#include "Animation.h"
#include "Enemy.h"

class Boss : public Enemy
{
private:
    Direction direction;
    int speed = 8;
    int xspeed = 16;
    int yspeed = 8;
    bool walking = false;
    int renderX = 1000;
    int renderY = 1000;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    string id;
    int moveTimer;
    bool dead = true;
    string entityName;
    ofImage sprite;

public:
    Boss(string id, int health, int baseDamage, string entityName, int ox, int oy, int ow, int oh);
    ~Boss();
    virtual int getOX() { return ox; };
    virtual int getOY() { return oy; };
    virtual bool isDead() { return dead; };
    virtual void kill() { this->dead = true; };
    virtual void revive() { this->dead = false; };
    virtual void setRenderX(int x) { renderX = x; };
    virtual void setRenderY(int y) { renderY = y; };
    virtual void inOverworldUpdate();
    virtual void fightingUpdate();
    virtual void inOverworldDraw();
    virtual void reset();
    virtual string getId() { return id; };
    virtual ofImage getSprite() { return overworldSprite; };
};