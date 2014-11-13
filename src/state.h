//
//  state.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#ifndef __emptyExample__state__
#define __emptyExample__state__

#include <iostream>

#include "ofMain.h"

class State{
    
public:
    State();
    void setup();
    virtual void update();
    virtual void draw();
    void exit();
    virtual void clear();
    virtual void touchDown(ofTouchEventArgs & touch);
    virtual void touchMoved(ofTouchEventArgs & touch);
    virtual void touchUp(ofTouchEventArgs & touch);
    
    virtual bool isExit();
    virtual State * getNextState();
};

#endif /* defined(__emptyExample__state__) */
