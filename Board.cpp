#include "Board.h"

Board::Board(int x, int y, int width, int height, int border) :
		x(x), y(y), width(width), height(height), border(border)
{ }

void Board::draw()
{
	glColor3f( 1.0, .8, .8 );
    glRectf( x - border, y - border, x + border + width, y );
    glRectf( x - border, y - border, x, y + height + border );
	glRectf( x + width + border, y + height + border, x + width, y-border);
	glRectf( x + width + border, y + height + border, x -border, y+height);
}