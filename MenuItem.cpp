/***************************************************************************//**
 * @file File containing the declaration for the Drawable class.
 *
 * @brief Contains the declaration for the Drawable class.
*******************************************************************************/

#include "MenuItem.h"

void MenuItem::draw()
{
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + (width), y + ( height ) );
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + (width) - border, y + ( height ) - border );
	text.setPosition( width/2, height/2 );
	text.setAlignment( 0 );
	text.draw();
}

void MenuItem::setPosition( double new_x, double new_y )
{
	x = new_x;
	y = new_y;
}

void MenuItem::setText( string new_text )
{
	text.setText( new_text );
}

void MenuItem::getClicked()
{

}
