#include "Area.h"

Area::Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Immovable *> immovables)
{
    this->name = name;
    this->nextArea = nextArea;
    areaImage.load(areaImagePath);
    areaMusic.load(areaMusicPath);
    areaStage.load(areaStagePath);
    this->entrancePosition = entrancePosition;
    this->enemies = enemies;
    this->immovables = immovables;
}

void Area::resetEnemies()
{
    for (unsigned int i = 0; i < enemies.size() - 1; i++)
        enemies.at(i)->revive();
}

void Area::spawnBosses()
{
    enemies.at(enemies.size() - 1)->revive();
}

int Area::getRemainingEnemies()
{
    int count = 0;
    for (unsigned int i = 0; i < enemies.size(); i++)
        if (!enemies.at(i)->isDead())
            count++;

    return count;
}
