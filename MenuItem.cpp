/***************************************************************************//**
 * @file File containing the implementation for the MenuItem class.
 *
 * @brief Contains the implementation for the MenuItem class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "MenuItem.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * Creates a given menu item with a size, location, and action
 * 
 * 
 * @param[in]      Menu* menu - the menu this item is a part of
 * @param[in]      double x - left most x cordinate of menuItem
 * @param[in]      double y - bottom most y cordinate of menuItem
 * @param[in]      double width - width of menu item
 * @param[in]      double height - height of menu item
 * @param[in]      double border - thickness of border around menuItem
 * @param[in]      string text - text to be displayed on menuItem
 * @param[in]      function<void ()> callback - action to be taken if menu 
						item is clicked
 *****************************************************************************/
MenuItem::MenuItem(Menu* menu, double x, double y, double width,double height,
				   double border, string text, function<void ()> callback) :
	menu(menu), x(x), y(y), width(width), height(height),
		border(border), text(0,0,0), callback(callback)
{
	//sets text
	this -> text.setPosition( x + width / 2, y + (height - border * 2) );
	this -> text.setSize( Pong::unit * 2 );
	this -> text.setAlignment( 0 );
	this -> text.setText( text );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * sets the bottom left coordinates of the MenuItem
 * 
 * 
 * @param[in]      double x - left most x coordinant
 * @param[in]      double y - bottom most y coordinant
 *****************************************************************************/
void MenuItem::setPosition( double x, double y )
{
	this -> x = x;
	this -> y = y;
	
	text.setPosition( x + width / 2, y + (height - border * 2));
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * sets the total width and height of the menu item
 * 
 * 
 * @param[in]      double width - width of menuItem
 * @param[in]      double height - height of menuItem
 *****************************************************************************/
void MenuItem::setSize( double width, double height )
{
	this -> width = width;
	this -> height = height;
	
	text.setPosition( x + width / 2, y + (height - border * 2) );
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * calls the PongText library to set the menuitem text
 * 
 * 
 * @param[in]      string text - the new text to be displayed
 *****************************************************************************/
void MenuItem::setText( string text )
{
	this -> text.setText(text);
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Sets the action of a given menuItem
 * 
 * 
 * @param[in]      function<void ()> callback - the given action function
 *****************************************************************************/
void MenuItem::setAction( function<void ()> callback )
{
	this -> callback = callback;
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * calls action if mouse clicked given menuItem
 * 
 * 
 * @param[in]      int button - which mouse button was pressed
 * @param[in]      int state - if the button is down or not
 * @param[in]      int x - x coordinant of button press
 * @param[in]      int y - y coordinant of button press
 * 
 * @returns true - if action was called
 * @returns false - if action was not called
 *****************************************************************************/
bool MenuItem::click( int button, int state, int x, int y )
{
	//checks if item was clicked
	if ( x >= this -> x && x <= this -> x + width && y >= this -> y && y <= this -> y + height )
	{
		if (state == GLUT_LEFT_BUTTON)
		{
			callback(); //calls given action
			return true;
		}
	}
	return false; //this item was not clicked
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * Draw the menuButton onto the menu
 *****************************************************************************/
void MenuItem::draw()
{
	// Draw the border
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + (width), y + ( height ) );
	
	// Draw black background
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + width - border, y + height - border );
    
    // Draw the text
	glColor3d( 1.0, 1.0, 1.0 );
	text.draw();
}
