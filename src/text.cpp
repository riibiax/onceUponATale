#include "text.h"


// Load all the texts, so it'd be faster to manipulate them "on the road"
//--------------------------------------------------------------
void Text::setup(){
    TTF.loadFont("fonts/Roboto-Light.ttf", 16);
    titleFont.loadFont("fonts/TRUEblood.ttf", 15);

    alpha = 0;
    grow = true;
    
    initializeVectorText();
    loadAllTexts();
    initializeCounters();

}


//--------------------------------------------------------------
void Text::initializeVectorText(){
    XML[1].story = "xml/hanselandgratel.xml";
    XML[2].story = "xml/pussinboots.xml";
    XML[3].story = "xml/cinderella.xml";
    XML[4].story = "xml/jackandthebeanstalk.xml";
    XML[5].story = "xml/littleredcap.xml";
}


//--------------------------------------------------------------
void Text::initializeCounters(){
    for(int i=1; i<BUF; i++){
        XML[i].counter = 0;
    }
}


//--------------------------------------------------------------
void Text::loadAllTexts(){
    for(int i=1; i<BUF; i++){
        XML[i].doc= loadText(XML[i].story);
    }
}


// In the beginning the user selects a card to read a story
// Define the index(global variable) to get the number of the story that we are reading
// Load the text of the selected story at 0 position
//--------------------------------------------------------------
void Text::setupText(int cardNumber){
    switch(cardNumber){
        case(1):
            index = 1;
            break;
        case(2):
            index = 2;
            break;
        case(3):
            index = 3;
            break;
        case(4):
            index = 4;
            break;
        case(5):
            index = 5;
            break;
        default:
            index = 0;
            break;
    }
    //main counter of paragraphes for the selected story
    XML[0].counter = 0;
    XML[0].doc= loadText(XML[index].story);
}


// load text using the name of xml file
//--------------------------------------------------------------
TiXmlDocument Text::loadText(string text){
    TiXmlDocument 	XML;
    string fullXmlFile = ofToDataPath(text);
    
    message = "loading " + text;
    
	bool loadOkay = XML.LoadFile(fullXmlFile);
    
    if (loadOkay)
		message = text+ " loaded from data folder!";
    else
		message = "unable to load " +text+ " check data/ folder";
    
    return XML;
}

//Get the title and draw it par blue!!
//TODO: fix the position
//--------------------------------------------------------------
void Text::drawTitle(int x, int y){
    string s = getTitle();
    ofDrawBitmapString("- ", x - titleFont.stringWidth(s) / 2 - 15, y);
    titleFont.drawString(s, x - titleFont.stringWidth(s) / 2, y);
    ofDrawBitmapString(" -", x + titleFont.stringWidth(s) / 2, y);
}


//Blending string
//--------------------------------------------------------------
void Text::updateAlpha(){
    //Blending string
    if (alpha >= 255)
        grow = false;
    else if (alpha<=0)
        grow = true;
    if (grow)
        alpha=alpha+5;
    else
        alpha=alpha-5;
}


//--------------------------------------------------------------
void Text::update(){
    //Blending string
    updateAlpha();
}


//Function to get the value of the attribute "title"
//--------------------------------------------------------------
string Text::getTitle(){
    
    TiXmlHandle storedHandle(&XML[0].doc);
    TiXmlElement* child = storedHandle.FirstChild("tale").FirstChild("title").ToElement();
    //just to be sure to get an element and his value
    if(child and child->GetText()){
        return child->GetText();
    }
    return " ";
}


//To get the value of the counter of the main story
//--------------------------------------------------------------
int Text::getCounterParagraph(int story){
    return     XML[story].counter;
}

//--------------------------------------------------------------
int Text::getNumParagraphes(int story){
    TiXmlHandle storedHandle(&XML[story].doc);
    
    int count = 0;
	for(TiXmlElement* child=storedHandle.FirstChild("tale").FirstChild("text").FirstChildElement("p").ToElement();child;child=child->NextSiblingElement("p"),count++){
		//nothing
	}
    return count;
}


void Text::drawJustifiedParagraph(int xPos, int yPos, float boxWidth){
    TiXmlHandle storedHandle(&XML[0].doc);
    TiXmlElement* p = storedHandle.FirstChild("tale").FirstChild("text").Child("p", XML[0].counter).ToElement();
    
    if(!p)
        return;

    //transfrom to a plain text paragraph
    string text_temp = "";
    for(TiXmlNode* elem = p->FirstChild(); elem != NULL; elem = elem->NextSibling()){
        TiXmlText* text = elem->ToText();
        
        if(text != NULL){
            text_temp.append(text->Value());
        }
        else{
            text_temp.append(" ");
            text_temp.append(elem->ToElement()->GetText());
            text_temp.append(" ");
        }
    }
    
    
    string line[20];
    int space_pixel_for_line[20];
    
    int line_counter = 0;
    
    //cut the paragraph in to lines according to the box width
    int start_index = 0;
    int end_index = 0;
    int number_of_space_in_line = 0;
    string line_without_space = "";
    int linespacing = TTF.getLineHeight()+10;
    cout << "text temp size: " << text_temp.size() << endl;
    
    string word = "";
    while (end_index < text_temp.size()) {
        
        end_index = text_temp.find(" ", start_index) ;
        word = text_temp.substr(start_index, end_index - start_index );
        
        if(TTF.stringWidth(line[line_counter]+word+" ")<boxWidth){
            line[line_counter].append(word + " ");
            line_without_space.append(word);
            start_index = end_index + 1;
            number_of_space_in_line++;
        }
        else{
            //calculate space pixel for each line
            space_pixel_for_line[line_counter] = (boxWidth - TTF.stringWidth(line_without_space))/number_of_space_in_line;
            cout << line[line_counter] << endl;
            cout << "space pixel = " << space_pixel_for_line[line_counter] << endl;
            
            //newline
            line_without_space = "";
            line_counter++;
            number_of_space_in_line = 0;
        }
    }
    // the last line is left align
    if(line[line_counter] == "")
        line[line_counter].append(word + " ");
    space_pixel_for_line[line_counter] = TTF.stringWidth("p");
    cout << line[line_counter] << endl;
    cout << "space pixel = " << space_pixel_for_line[line_counter] << endl;
    

        
    //DRAW THE PARAGRAPH
    //cout << "DRAWING" << endl;
    int letter_counter = 0;
    int line_counter2 = 0;
    touchZoneCounter = 0;
    

    int xCurr = xPos;
    int yCurr = yPos;

    for(TiXmlNode* elem = p->FirstChild(); elem != NULL; elem = elem->NextSibling()){

        ofSetColor(0, 0, 0, 255);
        TiXmlText* text = elem->ToText();
        
        //if the element is plain text, draw each character
        if(text != NULL){
            string temp = text->Value();
            
            for (int i=0; i<temp.size(); i++) {
                
                //new line
                if(letter_counter >= line[line_counter2].size()){
                    //cout << endl;
                    line_counter2++;
                    letter_counter = 0;

                    yCurr += linespacing;
                    xCurr = xPos;
                    
                }
                
                //draw a space
                if(temp.substr(i, 1)==" "){
                    
                    xCurr += space_pixel_for_line[line_counter2] + TTF.getLetterSpacing();
                    //cout << " ";
                    
                }
                //draw a letter
                else{
                    
                    TTF.drawString(temp.substr(i, 1), xCurr, yCurr);
                    //cout << temp.substr(i, 1);
                    xCurr = xCurr + TTF.stringWidth(temp.substr(i, 1))+ TTF.getLetterSpacing();
                
                }
                letter_counter++;


            }
        }
        
        else{
            string temp = elem->ToElement()->GetText();
            const char* attribute = elem->ToElement()->Attribute("type");

            //add a space after the word
            
            xCurr = xCurr + space_pixel_for_line[line_counter2] + TTF.getLetterSpacing();
            //cout << " ";
            
            letter_counter++;
            
            //if it's a NAME attribute, then set position values (for touching)
            if(strcmp(attribute, "name")==0 ){
                ofSetColor(0, 0, 0, alpha);
                touchZone[touchZoneCounter].characterNumber= ofToInt(elem->ToElement()->Attribute("n"));
                touchZone[touchZoneCounter].height= yCurr;
                touchZone[touchZoneCounter].startZone= xCurr;
            }
            
            for (int i=0; i< temp.length(); i++){
                //newline
                if(letter_counter >= line[line_counter2].size()){
                    line_counter2++;
                    letter_counter = 0;

                    yCurr += linespacing;
                    xCurr = xPos;
                    //cout << endl;
                    
                }
                
                if(temp.substr(i, 1)==" "){
                    xCurr = xCurr + space_pixel_for_line[line_counter2] + TTF.getLetterSpacing();
                    //cout << " ";
                }
                else{
                    TTF.drawString(temp.substr(i, 1), xCurr, yCurr);
                    xCurr = xCurr + TTF.stringWidth(temp.substr(i, 1)) + TTF.getLetterSpacing();
                    //cout << temp.substr(i, 1);
                }
                
                letter_counter++;

            }
            
            //set position values
            if(strcmp(attribute, "name")==0){
                touchZone[touchZoneCounter].endZone= xCurr;
                touchZoneCounter++;
            }
            
            //add a space after the word
           
            xCurr = xCurr + space_pixel_for_line[line_counter2] + TTF.getLetterSpacing();
            //cout << " ";
            
            letter_counter++;
            
        }

    }

}

//--------------------------------------------------------------
bool Text::nextParagraph(){
    XML[0].counter++;
    return updateImageIndex();
}

bool Text::lastParagraph(){
    if(XML[0].counter > 0){
        XML[0].counter--;
        return updateImageIndex();
    }
    return false;
}

int Text::getParagraphIndex(){
    return XML[0].counter;
}

bool Text::updateImageIndex(){
    TiXmlHandle storedHandle(&XML[0].doc);
    TiXmlElement* p = storedHandle.FirstChild("tale").FirstChild("text").Child("p", XML[0].counter).ToElement();
    
    if(!p)
        return false;
    
    const char* attr = p->Attribute("img");
    imageIndex =  ofToInt(ofToString(*attr));
    return true;
}

//--------------------------------------------------------------
void Text::findTheStory(int characterNumber){
    switch(characterNumber){
        case(1):
        case(2):
            index = 1;
            break;
        case(3):
        case(4):
            index = 2;
            break;
        case(5):
        case(6):
            index = 3;
            break;
        case(7):
        case(8):
            index = 4;
            break;
        case(9):
        case(10):
            index = 5;
            break;
        default:
            index = 0;
            break;
    }
}


//--------------------------------------------------------------
int Text::conversionCharacter(int characterNumber){
    switch(characterNumber){
        case(1):
        case(3):
        case(5):
        case(7):
        case(9):
            return 1;
        case(2):
        case(6):
        case(8):
        case(10):
            return 2;
        default:
            return 0;
    }
}

//--------------------------------------------------------------
void Text::changeValue(TiXmlElement* child, TiXmlElement* charIn, int character){
    string charInName = "";
    if(charIn->GetText())
        charInName = charIn->GetText();
    
    const char* tag = charIn->Value();
    
    
    for(TiXmlElement* alt = child->FirstChildElement("character"); alt; alt=alt->NextSiblingElement("character")){
        const char* attr = alt->Attribute("n");
        const char* attrType = alt->Attribute("type");
        if(ofToInt(ofToString(*attr))== character and strcmp(attrType, tag)==0){
            TiXmlNode* node = alt->FirstChild();
            node->Clear();
            node->SetValue(charInName);
        }
    }
    
    
}

//--------------------------------------------------------------
void Text::changeValues(TiXmlElement* child, TiXmlElement* charIn, int character){
    for (charIn = charIn->FirstChildElement(); charIn; charIn = charIn->NextSiblingElement()){
        changeValue(child, charIn, character);
	}
}


//--------------------------------------------------------------
void Text::changeCharacter(int characterOut, int characterIn){
    findTheStory(characterIn);
    characterOut = conversionCharacter(characterOut);
    characterIn = conversionCharacter(characterIn);
    TiXmlHandle storedHandle(&XML[0].doc);
    TiXmlElement* child = storedHandle.FirstChild("tale").FirstChild("text").Child("p", XML[0].counter).ToElement();
    TiXmlHandle storedHandleIn(&XML[index].doc);
    // looking for a node at the same level of the main story, so we could get a kind of paralelism
    TiXmlElement* childIn = storedHandleIn.FirstChild("tale").FirstChild("text").Child("p", XML[0].counter).ToElement();
    if (!childIn){
        //if it don't find a child, we continue to read the storyIn from the last read paragraph
        childIn = storedHandleIn.FirstChild("tale").FirstChild("text").Child("p", XML[index].counter).ToElement();
        if(!childIn){
            //if we are at the end of the chosen story, we restart from the first paragraph
            XML[index].counter = 0;
            childIn = storedHandleIn.FirstChild("tale").FirstChild("text").Child("p", XML[index].counter).ToElement();
        }
    }
    else
        // it found a paragraph at the same level of the main story, so the counter of the chosen story is the same of the main story
        XML[index].counter = XML[0].counter;
    
    TiXmlElement* charIn = storedHandleIn.FirstChild("tale").FirstChild("characters").Child("character", characterIn-1).ToElement();
    
    int count=1;
    // navigate in paragraphes
	for(child; child; child=child->NextSiblingElement(), count++){
        // find the first element having a child "character"
        for(TiXmlElement* alt = child->FirstChildElement("character"); alt; alt=alt->NextSiblingElement("character")){
            const char* attr = alt->Attribute("n");
            const char* attrType = alt->Attribute("type");
            if(ofToInt(ofToString(*attr))== characterOut and strcmp(attrType, "name")==0){
                if(count==1){
                    changeValues(child, charIn, characterOut);
                }
                else{
                    bool exit=false;
                    while(true){
                        for(TiXmlElement* altIn=childIn->FirstChildElement("character");altIn;altIn=altIn->NextSiblingElement("character")){
                            const char* attrIn = altIn->Attribute("n");
                            const char* attrTypeIn = altIn->Attribute("type");
                            if(ofToInt(ofToString(*attrIn))== characterIn  and strcmp(attrTypeIn, "name")==0){
                                //child->Clear();
                                //child->LinkEndChild(childIn->FirstChild());
                                exit=true;
                                break;
                            }
                        }
                        if(exit)
                            break;
                        else{
                            childIn=childIn->NextSiblingElement();
                            if(childIn)
                                XML[index].counter++;
                            else{
                                XML[index].counter = 0;
                                childIn = storedHandleIn.FirstChild("tale").FirstChild("text").Child("p", 0).ToElement();
                            }
                        }
                        
                    }
                }
            }
        }
    }
}




