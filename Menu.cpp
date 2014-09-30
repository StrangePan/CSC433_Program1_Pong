#include "Menu.h"

void Menu::draw()
{
	glColor3d( 1.0, 1.0, 1.0 );
	glRecti( x - (width / 2), y - (height / 2), x + (width / 2), y + ( height / 2 ) );
	glColor3d( 1.0, 1.0, 1.0 );
    glRecti( x - (width / 2) + border, y - (height / 2) + border, x + (width / 2) - border, y + ( height / 2 ) - border );
}
