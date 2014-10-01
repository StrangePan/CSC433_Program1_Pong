/***************************************************************************//**
 * @file File containing the declaration for the Menu class.
 *
 * @brief Contains the declaration for the Menu class.
*******************************************************************************/

#ifndef _MENU_H_
#define _MENU_H_

class Menu;

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include <string>
#include <list>
#include "Drawable.h"
#include "MenuItem.h"
#include "PongText.h"
#include "Pong.h"

using namespace std;

/***************************************************************************//**
 * @brief The M Class Holds all the information to draw a ball for Pong
 *
 * @details The Ball holds information for its position, speed, and size
*******************************************************************************/
class Menu : public Drawable
{
private:
	double x;
	double y;
	double width;
	double height;
	double border;
	list<MenuItem*> items;
	PongText title;

public:
	Menu(double x, double y, double width, double height, double border, string title);
	~Menu();
	
	void setPosition( double x, double y );
	void setSize( double width, double height );
	void setTitle( string title );
	void addItem( MenuItem* item );
	void setBorder( double border );
	void click( int button, int state, int x, int y );
	void draw();
	void clear();
};

#endif
