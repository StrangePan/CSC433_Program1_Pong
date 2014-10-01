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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
Menu::~Menu()
{
	clear();
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
void Menu::setTitle( string title )
{
	this -> title.setText( title );
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
void Menu::addItem(MenuItem* item)
{
	items.push_back(item);
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
void Menu::setBorder( double border )
{
	this -> border = border;
	
	title.setPosition( x + width / 2, y + height - border * 2 );
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
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
    glRectd( x + border, y + border, x + width - border * 2, y + height - border * 2);
    
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
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
void Menu::clear()
{
	for (MenuItem* item : items)
	{
		delete item;
	}
	items.clear();
}
