#include "Menu.h"

void Menu::draw()
{
	glColor3d( 1.0, 1.0, 1.0 );
	glRectd( x, y, x + (width ), y + ( height ) );
	glColor3d( 0.0, 0.0, 0.0 );
    glRectd( x + border, y + border, x + (width) - border, y + ( height ) - border );
	title.setPosition( width/2, height - border - 5 );
	title.setAlignment( 0 );
	title.draw();
}

void Menu::setPosition( double new_x, double new_y )
{
	x = new_x;
	y = new_y;
}

void Menu::setTitle( string new_title )
{
	title.setText( new_title );
}

void Menu::menuItemClicked( int clicked_x, int clicked_y)
{

}