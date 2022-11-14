#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area)
{
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
}

void OverworldState::loadArea(Area *area)
{
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}

void OverworldState::update()
{
    player->inOverworldUpdate();

    // If player health drops to zero, change to lose state
    if (player->getHealth() <= 0)
    {
        setNextState("End");
        setFinished(true);
        return;
    }

    // Damage over Time
    counter++;
    if ((area->getName() == "Area1_5") && (counter % 150 == 0))
    {
        if (player->getHealth() - 3 <= 0)
        {
            player->setHealth(0);
        }
        else
        {
            player->setHealth(player->getHealth() - 3);
        }
    }

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            area->getEnemies().at(i)->inOverworldUpdate();
            if (player->collides(area->getEnemies().at(i)))
            {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
                break;
            }
        }
    }


    camera->update();
}

void OverworldState::draw()
{
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->inOverworldDraw();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->inOverworldDraw();
        }
    }

    for (unsigned int i = 0; i < area->getImmovables().size(); i++)
    {
        int playerDistanceX = area->getImmovables().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getImmovables().at(i)->getOY() - camera->getPlayerY();
        area->getImmovables().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        area->getImmovables().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        area->getEnemies().at(i)->inOverworldDraw();
    }

    // HUD Implementation
    ofSetColor(ofColor::purple);
    ofDrawBitmapString(getArea()->getName().insert(4, " ") + "\nPlayer Health: " + ofToString(getPlayer()->getHealth()) + "\nRemaining Enemies: " + ofToString(getArea()->getRemainingEnemies()), 5, 15);
    ofSetColor(ofColor::white);
}

void OverworldState::keyPressed(int key)
{
    player->keyPressed(key);

    // Debug key reset health implementation
    if (key == 'h' || key == 'H')
    {
        player->setHealth(100);
    }

    // Debug key reset enemies implementation
    if (key == 'r' || key == 'R')
    {
        getArea()->resetEnemies();
    }
}

void OverworldState::keyReleased(int key)
{
    player->keyReleased(key);
}

void OverworldState::reset()
{
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}