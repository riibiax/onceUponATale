//
//  book.h
//  emptyExample
//
//  Created by Praiya Chinagarn on 10/13/56 BE.
//
//
#include "book.h"


//--------------------------------------------------------------
void Book::setup(){

    ofEnableAlphaBlending();
    
}

void Book::setup(int storyNumber){
    story = storyNumber;
    imagePageNumber = 1;
    is_end = false;
    
    text.setup();
    text.setupText(story);
    
    pageFont.loadFont("fonts/TRUEblood.ttf", 16);
    
    switch(storyNumber){
        case(HANSEL):
            //totalPage = TOTALPAGEHANSEL;
            character[0].index = CHAR_HANSEL_HANSEL;
            break;
        case(PUSS):
            //totalPage = TOTALPAGEPUSS;
            character[0].index = CHAR_PUSS_PUSS;
            break;
        default:
            break;
    }
    setBackground();
    setCharacter();
    setDecoration();
}

bool Book::isEnd(){
    if(is_end)
        cout << "END OF BOOK" << endl;
    return is_end;
}

void Book::turnPageForward(){
    if(text.nextParagraph()){
        imagePageNumber = text.imageIndex;
        setBackground();
        setCharacter();
        setDecoration();
    }
    else
        is_end = true;
    
}
/*
void test(){
    text.nextParagraph();
    imagePageNumber = text.imageindex
}
*/
void Book::turnPageBackward(){
    if(text.lastParagraph()){
        imagePageNumber = text.imageIndex;
        setBackground();
        setCharacter();
        setDecoration();
        
    }
    
}


void Book::changeCharacter(int fromChar,int toChar){ //change character 1 in the page to
    character[fromChar].index = toChar;
    setCharacter();
}

void Book::setBackground(){
    background.loadImage(getDirectory()+getBackgroundFileName());
}

void Book::setCharacter(){
    character[0].image.loadImage(getDirectory()+getCharFileName());
    setCharacterOption();
}

void Book::setCharacterOption(){
    switch(story){
        case(HANSEL):
            characterOption[0].image.loadImage("images/HanselAndGretel/card/carte_personnage_hansel.png");
            characterOption[1].image.loadImage("images/HanselAndGretel/card/carte_personnage_ogre.png");
            break;
        case(PUSS):
            characterOption[0].image.loadImage("images/PussBoots/card/carte_personnage_chat.png");
            characterOption[1].image.loadImage("images/PussBoots/card/carte_personnage_hansel.png");
            break;
        default:
            break;
    }
}

void Book::setDecoration(){
    switch(story){
        case(HANSEL):
            decoration.loadImage("images/HanselAndGretel/colone_HG.png");
            break;
        case(PUSS):
            decoration.loadImage("images/PussBoots/colone_PB.png");
            break;
        default:
            break;
    }
}

string convertInt(int number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

void Book::drawPageNumber(int x, int y){
    //string s = convertInt(imagePageNumber);
    string s = convertInt(text.getParagraphIndex()+1);
    pageFont.drawString(s, x - pageFont.stringWidth(s)/2, y - pageFont.stringHeight(s)/2);
}

void Book::drawChoosingCharacter(int x, int y){
    int ypos = y - characterOption[0].image.getHeight()/2;
    int xpos = x;
    for(int i=0; i<TOTALCHARACTEROPTION; i++){
        characterOption[i].image.draw(xpos, ypos);
        characterOption[i].position = ofVec2f(xpos, ypos);
        xpos = xpos + characterOption[0].image.getWidth() + 16; // 16 = space between images
    }
}

bool Book::isTouchOptionImage(int fromChar, ofVec2f fingerpos){
    for (int i=0; i<TOTALCHARACTEROPTION; i++) {
        if(fingerpos.x >= characterOption[i].position.x -10 && fingerpos.x <= characterOption[i].position.x + 10 + characterOption[i].image.width && fingerpos.y >= characterOption[i].position.y - 10 && fingerpos.y <= characterOption[i].position.y + 10 + characterOption[i].image.height) {// 10 = margin of touch area
            changeCharacter(fromChar,i);
            return true;
        }
    }
    return false;
}

string Book::getDirectory(){
    string dir = "";
    switch(story){
        case(HANSEL):            
            dir = "images/HanselAndGretel/HanselAndGretel_0" + convertInt(imagePageNumber) +"/";
            break;
        case(PUSS):
            dir = "images/PussBoots/PussBoots_0"+ convertInt(imagePageNumber) + "/";
            break;
        default:
            break;
    }
    return dir;
}

string Book::getBackgroundFileName(){
    string filename = "";
    switch(story){
        case(HANSEL):
            filename = "HG0" + convertInt(imagePageNumber) +"_decors_transparency.png";
            break;
        case(PUSS):
            filename = "PB0"+ convertInt(imagePageNumber) + "_decors_transparency.png";
            break;
        default:
            break;
    }
    return filename;
}

string Book::getCharFileName(){
    string filename = "";
    switch(story){
        case(HANSEL):
            switch (character[0].index) {
                case CHAR_HANSEL_HANSEL:
                    filename = "HG0" + convertInt(imagePageNumber) +"_hansel.png";
                    break;
                case CHAR_HANSEL_OGRE:
                    filename = "HG0" + convertInt(imagePageNumber) +"_ogre.png";
                    break;
                default:
                    break;
            }
            break;
        case(PUSS):
            switch (character[0].index) {
                case CHAR_PUSS_PUSS:
                    filename = "PB0" + convertInt(imagePageNumber) +"_chat.png";
                    break;
                case CHAR_PUSS_HANSEL:
                    filename = "PB0" + convertInt(imagePageNumber) +"_hansel.png";
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return filename;
}
