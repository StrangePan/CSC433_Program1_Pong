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
 * sets the bottom left coordinates of the function
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
 * sets the bottom left coordinates of the function
 * 
 * 
 * @param[in]      double x - left most x coordinant
 * @param[in]      double y - bottom most y coordinant
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
void MenuItem::setText( string text )
{
	this -> text.setText(text);
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
void MenuItem::setAction( function<void ()> callback )
{
	this -> callback = callback;
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
void MenuItem::click( int button, int state, int x, int y )
{
	if ( x >= this -> x && x <= this -> x + width && y >= this -> y && y <= this -> y + height )
	{
		if (state == GLUT_LEFT_BUTTON)
		{
			callback();
		}
	}
}

/**************************************************************************//**
 * @author Daniel Andrus,Johnny Ackerman
 * 
 * @par Description: 
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
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
