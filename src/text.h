//
//  text.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#ifndef __emptyExample__text__
#define __emptyExample__text__

#include <iostream>

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "tinyxml.h"


#define BUF 6
#define BUFFER 20



class Text {
    
public:
    
    void setup();
    void setupText(int cardNumber);
    void update();
    string getTitle();
    void drawTitle(int x, int y);
    void drawParagraph();
    void changeCharacter(int characterOut, int characterIn);
    bool nextParagraph();
    bool lastParagraph();
    int getParagraphIndex();
    
    void drawJustifiedParagraph(int xPos, int yPos, float boxWidth);
    
    int getCounterParagraph(int story);
    int getNumParagraphes(int story);
    
    struct strucTouchZone {
        int characterNumber;
        int startZone;
        int endZone;
        int height;
    } touchZone[BUFFER];
    
    int touchZoneCounter;

    int imageIndex;

    
private:
    
    TiXmlDocument loadText(string text);
    void initializeVectorText();
    void loadAllTexts();
    void initializeCounters();
    void changeValues(TiXmlElement* alt, TiXmlElement* charIn,  int character);
    void changeValue(TiXmlElement* alt, TiXmlElement* charIn,  int character);
    void findTheStory(int characterNumber);
    int conversionCharacter(int characterNumber);
    void updateAlpha();
    bool updateImageIndex();
    
    
    struct strucXML {
        TiXmlDocument doc;
        int           counter;
        string        story;
    } XML[BUF];
    
    int index;
    int alpha;
    
    string message;
    
    bool grow;
    
    ofTrueTypeFont TTF;
    ofTrueTypeFont titleFont;
};


#endif /* defined(__emptyExample__text__) */
