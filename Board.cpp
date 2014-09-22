#include "Board.h"

Board::Board(int x, int y, int width, int height, int border) :
		x(x), y(y), width(width), height(height), border(border),
		left_text(NULL), right_text(NULL)
{
	left_text = new (nothrow) unsigned char[1];
	right_text = new (nothrow) unsigned char[1];
	left_text[0] = '\0';
	right_text[0] = '\0';
}

Board::~Board()
{
	delete[] left_text;
	delete[] right_text;
}

void Board::setLeftText(string text)
{
	delete[] left_text;
	left_text = new (nothrow) unsigned char[text.size() + 1];
	for (unsigned int i = 0; i < text.size(); i++)
	{
		left_text[i] = (unsigned char) text[i];
	};
	left_text[text.size()] = '\0';
}

void Board::setRightText(string text)
{
	delete[] right_text;
	right_text = new (nothrow) unsigned char[text.size() + 1];
	for (unsigned int i = 0; i < text.size(); i++)
	{
		right_text[i] = (unsigned char) text[i];
	};
	right_text[text.size()] = '\0';
}

void Board::draw()
{
	glColor3d( 1.0, 0.8, 0.8 );
    glRecti( x - border, y - border, x + border + width, y );
    glRecti( x - border, y - border, x, y + height + border );
	glRecti( x + width + border, y + height + border, x + width, y-border);
	glRecti( x + width + border, y + height + border, x -border, y+height);

	glLineStipple(3, 0xAAAA );
	glEnable( GL_LINE_STIPPLE );
	glColor3d( 0.8, 1.0, 0.8 );
	glBegin( GL_LINES );
		glVertex2i( width/2, 0 );
		glVertex2i( width/2, height );
	glEnd();
	glDisable( GL_LINE_STIPPLE );

	glColor3d( 0.8, 0.8, 1.0 );
	glLineWidth( 1.5 );

	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 - 64) * 4.0, (height - 32) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, left_text);
    glPopMatrix();

	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 + 64) * 4.0, (height - 32) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, right_text);
    glPopMatrix();

}