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
 * @brief The Menu Class Holds all the information to Make the Menu for overall
				Pong
 *
 * @details The Menu has a location, size, border, title, and list of menuitems
*******************************************************************************/
class Menu : public Drawable
{
private:
	double x;	/*!< left most x coordinant */
	double y;	/*!< bottom most y coordinant */
	double width;	/*!< width of the menu */
	double height;	/*!< height of the menu */
	double border;	/*!< Thickness of menu border */
	list<MenuItem*> items;	/*!< list of menuitems in the menu */
	PongText title;	/*!< Menu Title */

public:
	/*!
	*  @brief The constructor, creates a menu with location, size, text, 
				and	list of menuitems
	*/
	Menu(double x, double y, double width, double height, double border, string title);

	/*!
	*  @brief The destructor, destroys the list of menu items
	*/
	~Menu();
	

	/*!
	*  @brief Sets the bottom left coordinants of the menu
	*/
	void setPosition( double x, double y );

	/*!
	*  @brief Sets the width and height of the menu
	*/
	void setSize( double width, double height );

	/*!
	*  @brief Sets the title of the menu
	*/
	void setTitle( string title );

	/*!
	*  @brief creates a new menuitem
	*/
	void addItem( MenuItem* item );

	/*!
	*  @brief changes the thickness of the border
	*/
	void setBorder( double border );

	/*!
	*  @brief determines what menuitem was clicked on
	*/
	void click( int button, int state, int x, int y );

	/*!
	*  @brief draws the menu
	*/
	void draw();

	/*!
	*  @brief used to delete the list of menuitems
	*/
	void clear();
};

#endif
