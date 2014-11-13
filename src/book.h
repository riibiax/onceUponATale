//
//  book.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//

#ifndef __emptyExample__book__
#define __emptyExample__book__

#include <iostream>
#include "ofMain.h"
#include "text.h"

#define HANSEL  1
#define PUSS    2

#define CHAR_HANSEL_HANSEL 0
#define CHAR_HANSEL_OGRE   1

#define CHAR_PUSS_PUSS   0
#define CHAR_PUSS_HANSEL 1

#define TOTALCHARACTER 1
#define TOTALCHARACTEROPTION 2

//#define TOTALPAGEHANSEL 8
//#define TOTALPAGEPUSS   9

class Book {
    
public:
    void setup();
    void setup(int storyNumber);
    void draw();
    void update();
    void turnPageForward();
    void turnPageBackward();
    void changeCharacter(int fromChar, int toChar);
    bool isEnd();
    void drawPageNumber(int x, int y);
    void drawChoosingCharacter(int x, int y);
    bool isTouchOptionImage(int fromChar, ofVec2f fingerpos);
    
    struct structChar{
        ofImage image;
        int     index;
    }character[TOTALCHARACTER];
    ofImage background;
    ofImage decoration;
    Text text;
    struct charOption{
        ofImage image;
        ofVec2f position;
    }characterOption[TOTALCHARACTEROPTION];
    //characterOption[TOTALCHARACTER][TOTALCHARACTEROPTION]

private:
    void setBackground();
    void setCharacter();
    void setCharacterOption();
    void setDecoration();
    string getDirectory();
    string getBackgroundFileName();
    string getCharFileName();
    
    int story;
    int imagePageNumber;
    //int totalPage;

    bool is_end;
    ofTrueTypeFont pageFont;
    
    
    /*struct strucCharacter {
        ofImage     file;
        ofPoint     position;
    } character[TOTALCHARACTER];*/
    

    
};


#endif /* defined(__emptyExample__book__) */
