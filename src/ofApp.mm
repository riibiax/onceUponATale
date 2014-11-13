#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    StateIntroduction * x = new StateIntroduction();
    setState(*x);
}

//--------------------------------------------------------------
void ofApp::setState(State & newstate){
    mState = &newstate;
}

//--------------------------------------------------------------
void ofApp::update(){
    mState->update();
    if(mState->isExit()){
        mState->clear();
        State * x = mState->getNextState();
        delete mState;
        setState(*x);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    mState->draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    mState->touchDown(touch);
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    mState->touchMoved(touch);
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    mState->touchUp(touch);
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
    
}
