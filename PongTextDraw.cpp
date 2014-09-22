#include "PongText.h"

void PongText::draw_char(char c, double x, double y, double size)
{
	const double u = size / 8;
	const double s = size;

	switch (toupper(c))
	{
		case '0':
			glRectf( x, y, x + u, y + s );
			glRectf( x + u * 3, y, x + u * 4, y + s );
			glRectf( x + u, y, x + u * 2, y + u );
			glRectf( x + u, y + s - u, x + u * 2, y + s );
			break;

		case '1':
			glRectf( x, y, x + u, y + s );
			break;

		case '2':
			glRectf( x, y, x + u * 4, y + u );
			glRectf( x + u * 3, y + u, x + u * 4, y + u * 3 );
			glRectf( x, y + u * 3, x + u * 4, y + u  *4 );
			glRectf( x, y + u * 4, x + u, y + s - u );
			glRectf( x + u, y + s - u, x + u * 4, y + s );
			break;

		case '3':
			glRectf( x, y, x + u * 3, y + u );
			glRectf( x + u * 3, y, x + u * 4, y + s );
			glRectf( x, y + u * 3, x + u * 3, y + u * 4 );
			glRectf( x, y + s - u, x + u * 3, y + s );
			break;

		case '4':
			glRectf( x, y, x + u, y + u * 3 );
			glRectf( x, y + u * 3, x + u * 3, y + u * 4 );
			glRectf( x + u * 3, y, x + u * 4, y + s );
			break;

		case '5':
			glRectf( x, y, x + u * 4, y + u );
			glRectf( x, y + u, x + u, y + u * 3 );
			glRectf( x, y + u * 3, x + u * 4, y + u * 4 );
			glRectf( x + u * 3, y + u * 4, x + u * 4, y + s - u );
			glRectf( x, y + s - u, x + u * 4, y + s );
			break;
	}
}
