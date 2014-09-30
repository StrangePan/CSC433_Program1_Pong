#include "Menu.h"

void Menu::draw()
{
	glColor3d( 1.0, 0.8, 0.8 );
	glRecti( x - (width / 2), y - (height / 2), x + (width / 2), y + ( height / 2 ) );
    glRecti( x - border, y - border, x, y + height + border );
}
