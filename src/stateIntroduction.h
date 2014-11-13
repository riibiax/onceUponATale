 //
//  stateIntroduction.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#ifndef __emptyExample__stateIntroduction__
#define __emptyExample__stateIntroduction__

#include <iostream>


#include "ofMain.h"
#include "state.h"
#include "stateReading.h"

#define TOTALSTORY 2


class StateIntroduction : public State{
    
public:
    
    StateIntroduction();
    void setup();
    void update();
    void draw();
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void clear();
    bool isExit();
    
private:   
    State * getNextState();

    int storyIndex;
    bool isexit;
    ofImage backgroundImage;
    ofTrueTypeFont titleFont;
    struct structStory {
        ofImage image;
        ofVec2f position;
    } story[TOTALSTORY];
    
    bool isTouchImage(structStory st_story, ofTouchEventArgs & touch);

};


#endif /* defined(__emptyExample__stateIntroduction__) */
