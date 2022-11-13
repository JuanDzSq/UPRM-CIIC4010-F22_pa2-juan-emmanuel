#include "PauseState.h"

PauseState::PauseState() {
    screen.load("images/ui/winscreen.png");
}

void PauseState::update() {
}

void PauseState::draw() {
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void PauseState::keyPressed(int key) {
    if(key == OF_KEY_ESC){
        if(getPrevState().compare("Overworld") == 0){
            setNextState("Overworld");
            setFinished(true);
        }
        else if(getPrevState().compare("Battle") == 0){
            setNextState("Battle");
            setFinished(true);
        }
    }
    
}

void PauseState::reset() {
    setFinished(false);
    setNextState("");
}