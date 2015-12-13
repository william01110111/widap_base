#pragma once

#include "WidapStd.h"
#include "WidapImage.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class WidapSfmlWindow
{
public:
	int getWdth() {return dim.x;} //returns the width
	int getHght() {return dim.y;} //returns the height
	XYint getDim() {return dim;} //returns the dimensions in the form of an XYint
	XYint getLoc() {return loc;}
	XYint getLocStrt() {return locStrt;}
	sf::RenderWindow * getWindowObj() {return &windowObj;}
	
	char nextKey();
	char lastKey();
	
	bool getShift() {return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);}
	bool getCtrl() {return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);}
	bool getAlt() {return sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);}
	bool getSuper() {return sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem) || sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);}
	
	XYint mouse() {return mouseLoc;}
	XYint mouseDlta() {return mouseLocDlta;}
	
	bool lClick() {return mouseLClick;}
	bool rClick() {return mouseRClick;}
	bool mClick() {return mouseMClick;}
	
	bool lDwn() {return mouseLDwn;}
	bool rDwn() {return mouseRDwn;}
	bool mDwn() {return mouseMDwn;}
	
	int scroll() {return mouseScroll;}
	
	bool hasFocus() {return windowHasFocus;}
	bool isOpen() {return windowIsOpen;}
	
	WidapSfmlWindow(); //constructor
	WidapSfmlWindow(int newWdth, int newHght, const char * name); //constructor, if dimensions are 0 it will be full screen
	
	~WidapSfmlWindow(); //destructor
	
	void open(int newWdth, int newHght, const char * name);
	
	void clrFill(RGBpix clr, double alpha=1); //fills the entire image with a single color
	
	void setLoc(XYint newLoc) {loc=newLoc; locStrt=newLoc;};
	
	void rect(int left, int right, int bottom, int top, RGBpix clr, double alpha=1); //draws a filled rectangle
	void circle(XYint pos, double radius, RGBpix clr, double alpha=1); //draws a filled circle (may be slightly off or look a bit polygony due to rounding, needs to be fixed)
	void target(int left, int right, int bottom, int top, int thickness, RGBpix clr, double alpha=1); //draws the corners of a square
	void finishPlygn(int thick, RGBpix clr) {line(loc, locStrt, thick, clr); loc=locStrt;} //good line drawing algorithm, alpha not yet implemented
	void line(XYint a, int thick, RGBpix clr) {line(loc, a, thick, clr); loc=a;} //good line drawing algorithm, alpha not yet implemented
	void line(XYint a, XYint b, int thick, RGBpix clr); //good line drawing algorithm, alpha not yet implemented
	void text(const char * txt, XYint newLoc, double pixHgh, RGBpix clr, double weight=1) {setLoc(newLoc); text(txt, pixHgh, clr, weight);} //draws text
	void text(char txt, XYint newLoc, double pixHgh, RGBpix clr, double weight=1) {setLoc(newLoc); text(txt, pixHgh, clr, weight);} //draws text
	void text(const char * txt, TextStyle style) {text(txt, style.height, style.color, style.weight);}
	void text(char txt, TextStyle style) {text(txt, style.height, style.color, style.weight);}
	void text(char txt, double pixHgh, RGBpix clr, double weight=1); //draws text
	void text(const char * txt, double pixHgh, RGBpix clr, double weight=1); //draws text
	
	void trnsfrFromImg(WidapImage* othrImg, XYint loc); //transfers this image to another
	
	void update(); //calls display and then checkInput
	void display();
	void checkInput();
	void close() {windowObj.close();}
	
private:
	
	XYint dim; //the dimensions of the bitmap
	XYint loc, locStrt; //used for where to draw text and polygons
	
	sf::RenderWindow windowObj;
	
	static bool firstInstance;
	static sf::Font font;
	static char key2char[127];
	
	XYint mouseLoc;
	XYint mouseLocDlta;
	bool mouseLClick, mouseRClick, mouseMClick;
	bool mouseLDwn, mouseRDwn, mouseMDwn;
	int mouseScroll;
	
	char keyPresses[64];
	int keyPressNum;
	int keyPressListPos;
	
	bool windowHasFocus;
	bool windowIsOpen;
	
	RGBApix *dataRGBA;
	sf::Texture texture;
	
	void windowResize();
};
