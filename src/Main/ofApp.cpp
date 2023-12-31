#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    initAreas();
    // Declaration and Initialization of States
    player = new Player(100, 6);
    titleState = new TitleState();
    overworldState = new OverworldState(player, currentArea);
    battleState = new BattleState(player, currentArea);
    winState = new WinState();
    endGameState = new EndGameState();
    pauseState = new PauseState();

    // Initial State
    currentState = titleState;
}

//--------------------------------------------------------------
void ofApp::initAreas()
{
    /**
     * @brief
     * each area is 672 pixels wide and 640 pixels high,
     * with 10 and 8 pixels of space between the player and the edge of the map respectively
     * each in-game pixel is 4 * 1 screen pixel
     */

//--------------Area 2----------------------------------------------------------------------------
    vector<Enemy *> enemies2;
    ofPoint entrancePosition2(4 * 110, 4 * 116);
    Enemy *area2Enemy1 = new Enemy("31", 30, 6, "enemy2", 4 * 120, 4 * 342, 50, 64);
    Enemy *area2Enemy2 = new Enemy("32", 30, 6, "enemy2", 4 * 254, 4 * 130, 50, 64);
    Enemy *area2Enemy3 = new Enemy("33", 30, 6, "enemy2", 4 * 542, 4 * 124, 50, 64);
    Enemy *area2Enemy4 = new Enemy("34", 30, 6, "enemy2", 4 * 532, 4 * 368, 50, 64);
    Enemy *area2Enemy5 = new Enemy("35", 30, 6, "enemy2", 4 * 266, 4 * 312, 50, 64);
    Enemy *area2Enemy6 = new Enemy("36", 30, 6, "enemy2", 4 * 194, 4 * 532, 50, 64);
    enemies2.push_back(area2Enemy1);
    enemies2.push_back(area2Enemy2);
    enemies2.push_back(area2Enemy3);
    enemies2.push_back(area2Enemy4);
    enemies2.push_back(area2Enemy5);
    enemies2.push_back(area2Enemy6);

    Boss *area2Boss = new Boss("B2", 40, 7, "boss2", 4 * 300, 4 * 300, 75, 96);
    enemies2.push_back(area2Boss);

    vector<Immovable *> immovables2;
    Immovable *area2Immovable1 = new Immovable("37", "immovable2", 4 * 100, 4 * 100);
    immovables2.push_back(area2Immovable1);

    area2 = new Area("Area2", NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2, immovables2);

//---------------Area 1_5--------------------------------------------------------------------------
    vector<Enemy *> enemies1_5;
    ofPoint entrancePosition1_5(4 * 85, 4 * 425);
    Enemy *area1_5Enemy1 = new Enemy("21", 20, 6, "enemy1_5", 4 * 375, 4 * 410, 50, 64);
    Enemy *area1_5Enemy2 = new Enemy("22", 20, 6, "enemy1_5", 4 * 225, 4 * 178, 50, 64);
    enemies1_5.push_back(area1_5Enemy1);
    enemies1_5.push_back(area1_5Enemy2);

    Boss *area1_5Boss = new Boss("B1_5", 40, 7, "boss1_5", 4 * 300, 4 * 300, 75, 96);
    enemies1_5.push_back(area1_5Boss);

    vector<Immovable *> immovables1_5;
    Immovable *area1_5Immovable1 = new Immovable("14", "immovable1_5", 4 * 100, 4 * 100);
    immovables1_5.push_back(area1_5Immovable1);

    area1_5 = new Area("Area1_5", area2, "images/areas/area1_5.png", "audio/SuperHero_original.ogg", "images/stages/stage1_5.png", entrancePosition1_5, enemies1_5, immovables1_5);

//---------------Area 1----------------------------------------------------------------------------
    vector<Enemy *> enemies1;
    ofPoint entrancePosition1(4 * 414, 4 * 566);
    Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432, 50, 64);
    Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178, 50, 64);
    Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178, 50, 64);
    enemies1.push_back(area1Enemy1);
    enemies1.push_back(area1Enemy2);
    enemies1.push_back(area1Enemy3);

    Boss *area1Boss = new Boss("B1", 40, 7, "boss1", 4 * 300, 4 * 300, 75, 96);
    enemies1.push_back(area1Boss);

    vector<Immovable *> immovables1;
    Immovable *area1Immovable1 = new Immovable("14", "immovable1", 4 * 100, 4 * 100);
    immovables1.push_back(area1Immovable1);


    area1 = new Area("Area1", area1_5, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, immovables1);
    currentArea = area1;
}

//--------------------------------------------------------------
void ofApp::update()
{
    currentState->update();
    if (currentState->hasFinished())
    {
        currentState->toggleMusic();
        if (currentState->getNextState() == "Title")
        {
            endGameState->setWin(false);
            area1->resetEnemies();
            area2->resetEnemies();
            area1_5->resetEnemies();
            currentArea = area1;
            battleState->reset();
            battleState->setStage(currentArea->getStage());
            overworldState->loadArea(currentArea);
            currentState = titleState;
        }
        else if (currentState->getNextState() == "Overworld")
        {
            pauseState->setPrevState(currentState->getNextState());             //Saves current state name, for use in Pause State
            currentState = overworldState;
        }
        else if (currentState->getNextState() == "Battle")
        {
            pauseState->setPrevState(currentState->getNextState());             //Saves current state name, for use in Pause State
            if(currentState != pauseState){                                     //This is so that enemy health does not reset when pausing and unpausing
                battleState->startBattle(overworldState->getEnemy());           
            }
            currentState = battleState;
        }
        else if (currentState->getNextState() == "Win")
        {

            overworldState->getEnemy()->kill();
            bossCheck = overworldState->getEnemy()->getId();
            if (bossCheck.compare("B1") == 0 || bossCheck.compare("B1_5") == 0 || bossCheck.compare("B2") == 0)     //If boss killed go to next area
            {
                if (currentArea->getNextArea() == NULL)
                {
                    endGameState->setWin(true);
                    currentState = endGameState;
                    player->reset();                //Reset health when game is finished
                }
                else
                {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            }
            else                                    //If all enemies are dead, spawn boss
            {
                if(currentArea->getRemainingEnemies() == 0){
                    currentArea->getEnemies().at(currentArea->getEnemies().size() - 1)->revive();
                }
                currentState = winState;
            }
        }
        // else if (currentState->getNextState() == "End")          //This state is not in use
        // {
        //     currentState = endGameState;
        //     player->reset();
        // }
        else if(currentState->getNextState() == "PauseState")            //PauseState
        {
            currentState = pauseState;
        }
        currentState->toggleMusic();
        currentState->reset();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == OF_KEY_ESC && (currentState == overworldState || currentState == battleState)){  //Press esc key to set to Pause State
        currentState->setNextState("PauseState");
        currentState->setFinished(true);
    }
    else{currentState->keyPressed(key);}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    currentState->dragEvent(dragInfo);
}