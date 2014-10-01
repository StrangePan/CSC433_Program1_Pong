/***************************************************************************//**
 * @file File containing the declaration for the MenuItem class.
 *
 * @brief Contains the declaration for the MenuItem class.
*******************************************************************************/
#ifndef _MENUITEM_H_
#define _MENUITEM_H_

class MenuItem;

#include <string>
#include <functional>
#include "Drawable.h"
#include "PongText.h"
#include "Pong.h"
#include "Menu.h"

using namespace std;

class MenuItem : public Drawable
{
private:
	Menu* menu;
	double x;
	double y;
	double width;
	double height;
	double border;
	PongText text;
	function<void ()> callback;

public:
	MenuItem(Menu* menu, double x, double y, double width, double height, string text, function<void ()> callback = [](){});
	
	void setPosition( double x, double y );
	void setSize( double width, double height );
	void setText( string text );
	void setAction( function<void ()> callback );
	void click( int button, int state, int x, int y );
	void draw();
};

#endif
