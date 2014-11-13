//
//  stateReading.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#ifndef __emptyExample__stateReading__
#define __emptyExample__stateReading__

#include <iostream>

#pragma once

#include "ofMain.h"

#include "state.h"
#include "stateIntroduction.h"

#include "book.h"

#define DRAGLEFT 1
#define DRAGRIGHT 2


class StateReading : public State{
    
public:
    StateReading(int story);
    
    void setup(int story);
    void update();
    void draw();
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void clear();
    bool isExit();
    
private:
    
    bool isexit;
    State * getNextState();
    void drawParagraph();
    
    ofVec2f touchStart;
    ofVec2f touchEnd;
    ofImage backgroundImage;
    ofImage homeIcon;
    ofVec2f homeIconPosition;
        
    Book book;
    
    bool is_show_choosing_char_screen;
    int characterToChange;
};



#endif /* defined(__emptyExample__stateReading__) */
