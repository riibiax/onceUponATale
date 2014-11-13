//
//  stateReading.cpp
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#include "stateReading.h"


//--------------------------------------------------------------
StateReading::StateReading(int story) : State::State(){
    setup(story);
    isexit = false;
    is_show_choosing_char_screen = false;
}


//--------------------------------------------------------------
void StateReading::setup(int story){
    backgroundImage.loadImage("images/fond_gris.png");
    homeIcon.loadImage("images/home_small.png");
    homeIconPosition = ofVec2f(80,45);
    book.setup(story);
}


//--------------------------------------------------------------
void StateReading::update(){
    if (book.isEnd()) {
        isexit = true;
    }
    book.text.update(); //blinking text
}


//--------------------------------------------------------------
void StateReading::draw(){
    ofSetColor(255, 255, 255, 255);
    backgroundImage.draw(0, 0);
    homeIcon.draw(homeIconPosition);
    book.background.draw(0, 60);
    book.character[0].image.draw(0, 60);
    book.decoration.draw(0, 15);
    
    ofSetColor(0, 0, 0, 255);
    book.text.drawTitle(ofGetWidth()/2, 60 );
    book.text.drawJustifiedParagraph(ofGetWidth()/4 - 20, ofGetHeight()/2 + 100, 450);
    book.drawPageNumber(ofGetWidth()/2+5, ofGetHeight() - 60);

    ofSetColor(255, 255, 255, 255);
    if (is_show_choosing_char_screen) {
        book.drawChoosingCharacter(140, ofGetHeight()/2);
    }
}

//--------------------------------------------------------------
void StateReading::touchDown(ofTouchEventArgs & touch){
    touchStart = ofVec2f(touch.x, touch.y);
    touchEnd = ofVec2f(touch.x, touch.y);
}


//--------------------------------------------------------------
void StateReading::touchMoved(ofTouchEventArgs & touch){
    touchEnd = ofVec2f(touch.x, touch.y);
    cout << "touchmove" << endl;
}


//--------------------------------------------------------------
void StateReading::touchUp(ofTouchEventArgs & touch){

    cout << "touch 1" << endl;

    if(!is_show_choosing_char_screen){
        //NAVIGATE
        //swipe
        float dist = touchEnd.x - touchStart.x;
        if (dist > 50)
            book.turnPageBackward();
        else if (dist < -50)
            book.turnPageForward();
        //tap left or right of the page
        else if(touch.x < 200)
            book.turnPageBackward();
        else if(touch.x > ofGetWidth() - 200)
            book.turnPageForward();
        
        //HOME ICON
        if(touch.x >= homeIconPosition.x - 5 and touch.x <= homeIconPosition.x + homeIcon.width + 5 and touch.y >= homeIconPosition.y - 5 and touch.y <= homeIconPosition.y + homeIcon.height + 5){
            cout << "EXIT" << endl;
            
            isexit = true;
        }

        //CHANGING 
        
        //todo: put this into a function in book.cpp
        //check if the blinking text is selected
        for(int i=0; i<book.text.touchZoneCounter; i++){
            if(touch.x >=book.text.touchZone[i].startZone-10 and touch.x<=book.text.touchZone[i].endZone+10 and touch.y>=book.text.touchZone[i].height-20 and touch.y<=(book.text.touchZone[i].height+30)){
                characterToChange = book.text.touchZone[i].characterNumber - 1;
                is_show_choosing_char_screen = true;
                cout << "changing character " << characterToChange << endl;
            }
        }
    }
    else{
        if(book.isTouchOptionImage(characterToChange, ofVec2f(touch.x, touch.y)))
            is_show_choosing_char_screen = false;
    }
    

    touchStart = ofVec2f(0,0);
    touchEnd = ofVec2f(0,0);
}


//--------------------------------------------------------------
bool StateReading::isExit(){
    return isexit;
}


//--------------------------------------------------------------
void StateReading::clear(){

}


//--------------------------------------------------------------
State * StateReading::getNextState(){
    StateIntroduction * x = new StateIntroduction();
    return x;
}

