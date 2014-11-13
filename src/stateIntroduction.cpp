
#include "stateIntroduction.h"


//--------------------------------------------------------------
StateIntroduction::StateIntroduction() : State::State(){
    setup();
    isexit = false;
}


//--------------------------------------------------------------
void StateIntroduction::setup(){
    storyIndex=0;
    backgroundImage.loadImage("images/fond_gris.png");
    titleFont.loadFont("fonts/TRUEblood.ttf", 20);
    story[0].image.loadImage("images/Intro/carte_conte_hanselAndGretel.png");
    story[1].image.loadImage("images/Intro/carte_conte_pussBoots.png");
}

//--------------------------------------------------------------
void StateIntroduction::update(){
    if(storyIndex!=0)
        isexit = true;
}


//--------------------------------------------------------------
void StateIntroduction::draw(){
    ofSetColor(255, 255, 255);
    backgroundImage.draw(0, 0);
    //ofSetColor(0, 0, 0, 255* (sin( ofGetElapsedTimef() * 3) * 0.5f + 0.5f));
    int ypos = ofGetHeight()/2 - story[0].image.getHeight()/2;
    int xpos = 90;
    for(int i=0; i<TOTALSTORY; i++){
        story[i].image.draw(xpos, ypos);
        story[i].position = ofVec2f(xpos, ypos);
        xpos = xpos + story[i].image.getWidth() + 16; // 16 = space between 2 images
    }
    ofSetColor(0, 0, 0);
    string msg = "CHOOSE YOUR FAIRY TALE";
    titleFont.drawString(msg, (ofGetWidth()-titleFont.stringWidth(msg))/2, 200);
}

bool StateIntroduction::isTouchImage(structStory st_story, ofTouchEventArgs & touch){
    
    if(touch.x >= st_story.position.x -20 && touch.x <= st_story.position.x + 20 + st_story.image.width && touch.y >= st_story.position.y - 20 && touch.y <= st_story.position.y + 20 + st_story.image.height) // 20 = margin of touch area
        return true;

    return false;
}
//--------------------------------------------------------------
void StateIntroduction::touchDown(ofTouchEventArgs & touch){

}


//--------------------------------------------------------------
void StateIntroduction::touchMoved(ofTouchEventArgs & touch){

}


//--------------------------------------------------------------
void StateIntroduction::touchUp(ofTouchEventArgs & touch){
    for (int i=0; i<TOTALSTORY; i++) {
        if(isTouchImage(story[i], touch))
            storyIndex = i+1;
    }
}


//--------------------------------------------------------------
bool StateIntroduction::isExit(){
    return isexit;
}


//--------------------------------------------------------------
void StateIntroduction::clear(){
    for(int i=0; i<TOTALSTORY; i++)
        story[i].image.clear();
    ofSetColor(255, 255, 255);

}


//--------------------------------------------------------------
State * StateIntroduction::getNextState(){
    StateReading * x= new StateReading(storyIndex);
    return x;
}


