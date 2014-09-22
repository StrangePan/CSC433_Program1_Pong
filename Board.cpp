#include "Board.h"

Board::Board(int x, int y, int width, int height, int border) :
		x(x), y(y), width(width), height(height), border(border),
		left_text( width / 2 - Pong::unit * 4, height - Pong::unit * 2, Pong::unit * 8, "", -1 ),
		right_text( width / 2 + Pong::unit * 4, height - Pong::unit * 2, Pong::unit * 8, "", 1 )
{ }

Board::~Board()
{ }

void Board::setLeftText(string text)
{
	left_text.setText(text);
}

void Board::setRightText(string text)
{
	right_text.setText(text);
}

void Board::draw()
{
	glColor3f( 1.0, 1.0, 1.0 );
    glRecti( x - border, y - border, x + border + width, y );
    glRecti( x - border, y - border, x, y + height + border );
	glRecti( x + width + border, y + height + border, x + width, y-border);
	glRecti( x + width + border, y + height + border, x -border, y+height);

	glLineStipple(Pong::unit / 2, 0xAAAA );
	glEnable( GL_LINE_STIPPLE );
	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_LINES );
		glVertex2i( width/2, 0 );
		glVertex2i( width/2, height );
	glEnd();

	left_text.draw();
	right_text.draw();
}