/***************************************************************************//**
 * @file File containing the declaration for the Drawable class.
 *
 * @brief Contains the declaration for the Drawable class.
*******************************************************************************/

#include "Menu.h"

Menu::Menu(double x, double y, double width, double height, double border, string title) :
		x(x), y(y), width(width), height(height), border(border), title(0,0,0)
{
	this -> title.setPosition( x + width / 2, y + height - border - 5 );
	this -> title.setSize( Pong::unit * 2 );
	this -> title.setAlignment( 0 );
	this -> title.setText( title );
}
Menu::~Menu()
{
	clear();
}


void Menu::setPosition( double x, double y )
{
	this -> x = x;
	this -> y = y;
	
	title.setPosition( x + width / 2, y + height - border - 5 );
}

void Menu::setSize( double width, double height )
{
	this -> width = width;
	this -> height = height;
	
	title.setPosition( x + width / 2, y + height - border - Pong::unit );
}

void Menu::setTitle( string title )
{
	this -> title.setText( title );
}

void Menu::addItem(MenuItem* item)
{
	items.push_back(item);
}

void Menu::setBorder( double border )
{
	this -> border = border;
	
	title.setPosition( x + width / 2, y + height - border - 5 );
}

void Menu::click( int button, int state, int x, int y )
{
	for (MenuItem* item : items)
	{
		item -> click(button, state, x, y);
	}
}

void Menu::draw()
{
	// Draw transparent overlay
	glColor4d( 0.0, 0.0, 0.0, 0.5 );
	glRectd( 0, 0, Pong::getInstance()->getViewWidth(), Pong::getInstance()->getViewHeight() );
	
	// Draw border
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + width, y + height );
	
	// Draw black background
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + width - border, y + height - border );
    
    // Draw title and menu items
    title.draw();
    for (MenuItem* item : items)
    {
	    item -> draw();
    }
}

void Menu::clear()
{
	for (MenuItem* item : items)
	{
		delete item;
	}
	items.clear();
}
