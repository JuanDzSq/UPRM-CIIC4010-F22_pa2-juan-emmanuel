#pragma once

#include "Animation.h"
#include "Entity.h"

class Immovable : public Entity
{
private:
    // Direction direction;
    // int speed = 8;
    // int xspeed = 16;
    // int yspeed = 8;
    // bool walking = false;
    int renderX = 1000;
    int renderY = 1000;
    // Animation *walkUp;
    // Animation *walkDown;
    // Animation *walkLeft;
    // Animation *walkRight;
    // Animation *fighting;
    string id;
    // int moveTimer;
    // bool dead = false;
    string entityName;
    ofImage sprite;

public:
    Immovable(string id, string entityName, int ox, int oy);
    ~Immovable();
    int getOX() { return ox; };
    int getOY() { return oy; };
    // bool isDead() { return dead; };
    // void kill() { this->dead = true; };
    // void revive() { this->dead = false; };
    void setRenderX(int x) { renderX = x; };
    void setRenderY(int y) { renderY = y; };
    // void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw();
    void reset();
    string getId() { return id; };
    ofImage getSprite() { return overworldSprite; };
};