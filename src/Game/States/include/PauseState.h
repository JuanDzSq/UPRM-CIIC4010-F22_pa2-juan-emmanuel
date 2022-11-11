//PushState.h

#pragma once

#include "Enemy.h"
#include "Player.h"
#include "State.h"

class PauseState : public State {
   private:
    ofImage screen;

   public:
    PauseState();
    void update();
    void draw();
    void keyPressed(int key);
    void reset();
    string prevState;
};
