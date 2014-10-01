/***************************************************************************//**
 * @file File containing the declaration for the MenuItem class.
 *
 * @brief Contains the declaration for the MenuItem class.
*******************************************************************************/
#ifndef _MENUITEM_H_
#define _MENUITEM_H_

class MenuItem;

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include <string>
#include <functional>
#include "Drawable.h"
#include "PongText.h"
#include "Pong.h"
#include "Menu.h"

using namespace std;

/***************************************************************************//**
 * @brief The MenuItem class creates each clickable item in the menu
 *
 * @details MenuItem holds the location of the item, its text, and it's 
				function
*******************************************************************************/
class MenuItem : public Drawable
{
private:
	Menu* menu;	/*!< istance of the menu that this item is on */
	double x;	/*!< bottom left x coordinant of item */
	double y;	/*!< bottom left y coordinant of item */
	double width;	/*!< width of menu item with border */
	double height;	/*!< height of menu item with border */
	double border;	/*!< size of border around menu item */
	PongText text;	/*!< The text displayed on the item */
	function<void ()> callback;	/*!< The function the item calls */

public:
	/*!
	*  @brief The constructor, creates a menu item with location, size, text, 
				and	action
	*/
	MenuItem(Menu* menu, double x, double y, double width, double height, string text, function<void ()> callback = [](){});
	

	/*!
	*  @brief sets the bottom left coordinates
	*/
	void setPosition( double x, double y );

	/*!
	*  @brief sets the size of the item
	*/
	void setSize( double width, double height );

	/*!
	*  @brief Sets the item lable
	*/
	void setText( string text );

	/*!
	*  @brief Sets the items action function
	*/
	void setAction( function<void ()> callback );

	/*!
	*  @brief The location and button pressed by the mouse
	*/
	void click( int button, int state, int x, int y );

	/*!
	*  @brief draws the menu item
	*/
	void draw();
};

#endif
