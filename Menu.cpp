/***************************************************************************//**
 * @file File containing the implementation for the Menu class.
 *
 * @brief Contains the implementation for the Menu class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Menu.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * Creates a menu with size, postion, and list of menuItems
 * 
 * 
 * @param[in]      double x - left Most x component of the Menu
 * @param[in]      double y - bottom Most y component of the Menu
 * @param[in]      double width - total width of Menu
 * @param[in]      double height - total height of Menu
 * @param[in]      double border - thickness of the border
 * @param[in]      string title	- name given to border
 *****************************************************************************/
Menu::Menu(double x, double y, double width, double height, double border, string title) :
		x(x), y(y), width(width), height(height), border(border), title(0,0,0)
{
	this -> title.setPosition( x + width / 2, y + height - border * 2 );
	this -> title.setSize( Pong::unit * 2 );
	this -> title.setAlignment( 0 );
	this -> title.setText( title );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Deletes list of menu Items
 *****************************************************************************/
Menu::~Menu()
{
	clear();
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Sets the bottom left possition of the Menu
 * 
 * 
 * @param[in]      double x - left most x coordinant
 * @param[in]      double y - bottom most y coordinant
 *****************************************************************************/
void Menu::setPosition( double x, double y )
{
	this -> x = x;
	this -> y = y;
	
	title.setPosition( x + width / 2, y + height - border * 2 );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Sets the Size of the Menu
 * 
 * 
 * @param[in]      double width - total width of Menu
 * @param[in]      double height - total height of Menu
 *****************************************************************************/
void Menu::setSize( double width, double height )
{
	this -> width = width;
	this -> height = height;
	
	title.setPosition( x + width / 2, y + height - border * 2 );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Sets the Title of the Menu
 * 
 * 
 * @param[in]      string title - The new Title
 *****************************************************************************/
void Menu::setTitle( string title )
{
	this -> title.setText( title );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Adds a new Menu Item to list
 * 
 * 
 * @param[in]      MenuItem* item - New Item to be added
 *****************************************************************************/
void Menu::addItem(MenuItem* item)
{
	items.push_back(item);
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Sets the border Thickness
 * 
 * 
 * @param[in]      double border - New Border Thickness
 *****************************************************************************/
void Menu::setBorder( double border )
{
	this -> border = border;
	
	title.setPosition( x + width / 2, y + height - border * 2 );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * founction determines which menu Item was pressed
 * 
 * 
 * @param[in]      int button - which mouse button was pressed
 * @param[in]      int state - whether the button is still pressed
 * @param[in]      int x - x coordinant of the mouse
 * @param[in]      int y - y coordinant of the mouse
 *****************************************************************************/
void Menu::click( int button, int state, int x, int y )
{
	for (MenuItem* item : items)
	{
		if (item -> click(button, state, x, y)) return;
	}
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Draws the given Menu
 *****************************************************************************/
void Menu::draw()
{
	// Draw transparent overlay
	//glColor4d( 0.0, 0.0, 0.0, 0.5 );
	//glRectd( 0, 0, Pong::getInstance()->getViewWidth(), Pong::getInstance()->getViewHeight() );
	
	// Draw border
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + width, y + height );
	
	// Draw black background
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + width - border, y + height - border);
    
    // Draw title and menu items
	glColor3d( 1.0, 1.0, 1.0 );
    title.draw();
    for (MenuItem* item : items)
    {
	    item -> draw();
    }
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Clears all Menu Items in the List
 *****************************************************************************/
void Menu::clear()
{
	for (MenuItem* item : items)
	{
		delete item;
	}
	items.clear();
}
