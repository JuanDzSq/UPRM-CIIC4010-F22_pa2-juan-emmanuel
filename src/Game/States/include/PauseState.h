#pragma once

#include "Enemy.h"
#include "Player.h"
#include "State.h"

class PauseState : public State {
   private:
    ofImage screen;
    string prevState;

   public:
    PauseState();
    void update();
    void draw();
    void keyPressed(int key);
    void reset();
    string getPrevState(){return prevState;}
    void setPrevState(string prevState){this->prevState = prevState;}
};
