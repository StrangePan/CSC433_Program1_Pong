#include "PongText.h"

void PongText::draw_char(char c, double x, double y, double size)
{
	const double u = size / 8;
	const double s = size;

	switch (toupper(c))
	{
		default:
			break;

		case '0':
			glRectd( x, y, x + u, y + s );
			glRectd( x + u * 3, y, x + u * 4, y + s );
			glRectd( x + u, y, x + u * 2, y + u );
			glRectd( x + u, y + s - u, x + u * 2, y + s );
			break;

		case '1':
			glRectd( x, y, x + u, y + s );
			break;

		case '2':
			glRectd( x, y, x + u * 4, y + u );
			glRectd( x + u * 3, y + u, x + u * 4, y + u * 3 );
			glRectd( x, y + u * 3, x + u * 4, y + u  *4 );
			glRectd( x, y + u * 4, x + u, y + s - u );
			glRectd( x + u, y + s - u, x + u * 4, y + s );
			break;

		case '3':
			glRectd( x, y, x + u * 3, y + u );
			glRectd( x + u * 3, y, x + u * 4, y + s );
			glRectd( x, y + u * 3, x + u * 3, y + u * 4 );
			glRectd( x, y + s - u, x + u * 3, y + s );
			break;

		case '4':
			glRectd( x, y, x + u, y + u * 3 );
			glRectd( x, y + u * 3, x + u * 3, y + u * 4 );
			glRectd( x + u * 3, y, x + u * 4, y + s );
			break;

		case '5':
			glRectd( x, y, x + u * 4, y + u );
			glRectd( x, y + u, x + u, y + u * 3 );
			glRectd( x, y + u * 3, x + u * 4, y + u * 4 );
			glRectd( x + u * 3, y + u * 4, x + u * 4, y + s - u );
			glRectd( x, y + s - u, x + u * 4, y + s );
			break;
	}
}
