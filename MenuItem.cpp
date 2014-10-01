/***************************************************************************//**
 * @file File containing the declaration for the Drawable class.
 *
 * @brief Contains the declaration for the Drawable class.
*******************************************************************************/

#include "MenuItem.h"

MenuItem::MenuItem(Menu* menu, double x, double y, double width, double height, string text, function<void ()> callback) :
	menu(menu), x(x), y(y), width(width), height(height), text(0,0,0), callback(callback)
{
	this -> text.setPosition( x + width / 2, y + (height - border * 2) - Pong::unit );
	this -> text.setSize( Pong::unit * 2 );
	this -> text.setAlignment( 0 );
	this -> text.setText( text );
}

void MenuItem::setPosition( double x, double y )
{
	this -> x = x;
	this -> y = y;
	
	text.setPosition( x + width / 2, y + (height - border * 2) - Pong::unit );
}

void MenuItem::setSize( double width, double height )
{
	this -> width = width;
	this -> height = height;
	
	text.setPosition( x + width / 2, y + (height - border * 2) - Pong::unit );
}

void MenuItem::setText( string text )
{
	this -> text.setText(text);
}

void MenuItem::setAction( function<void ()> callback )
{
	this -> callback = callback;
}

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

void MenuItem::draw()
{
	// Draw the border
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + (width), y + ( height ) );
	
	// Draw black background
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + width - border, y + height - border );
    
    // Draw the text
	text.draw();
}
