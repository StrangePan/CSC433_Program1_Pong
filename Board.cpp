#include "Board.h"

Board::Board(int x, int y, int width, int height, int border) :
		x(x), y(y), width(width), height(height), border(border)
{ }

void Board::draw()
{
	score_1 = "0";
	score_2 = "0";

	glColor3f( 1.0, .8, .8 );
    glRectf( x - border, y - border, x + border + width, y );
    glRectf( x - border, y - border, x, y + height + border );
	glRectf( x + width + border, y + height + border, x + width, y-border);
	glRectf( x + width + border, y + height + border, x -border, y+height);

	glLineStipple(3, 0xAAAA );
	glEnable( GL_LINE_STIPPLE );
	glColor3f( .8, 1.0, .8 );
	glBegin( GL_LINES );
		glVertex2f( width/2, 0 );
		glVertex2f( width/2, height );
	glEnd();

	glColor3f( .8, .8, 1.0 );
	glRasterPos2f( width / 2 - 64, height - 32 );

	glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, ( const unsigned char *)  score_1 );

	glRasterPos2f( width / 2 + 64, height - 32 );

	glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *) score_2 );
}