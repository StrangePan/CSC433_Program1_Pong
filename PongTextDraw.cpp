/***************************************************************************//**
 * @file File containing the implementation for the PongText class.
 *
 * @brief Contains the implementation for the PongText class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "PongText.h"

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * draws a single charactor in a blocky formate
 * 
 * 
 * @param[in]      char c - the charactor being drawn
 * @param[in]      double x - x coordinant of charactor
 * @param[in]      double y - y coordinant of charactor
 * @param[in]      double size - size of charactor
 *****************************************************************************/
void PongText::draw_char(char c, double x, double y, double size)
{
	const double u = size / 8;	// Unitary size
	const double s = size;		// Sugar :P

	/* Note on drawing order for debugging purposes:
	 * Vertical lines first from left to right then top to bottom
	 * Horizontal lines next from top to bottom then left to right
	 * Single point drawing order varies between characters
	*/

	switch (toupper(c))
	{
		default:
			break;

		case '0':
		case 'O':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case '1':
			glRectd( x, y, x + u, y - s );
			break;

		case '2':
			glRectd( x, y - u * 3, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 4 );
			glRectd( x, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 4, y - s );
			break;

		case '3':
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x, y, x + u * 3, y - u );
			glRectd( x, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x, y - s + u, x + u * 3, y - s );
			break;

		case '4':
			glRectd( x, y, x + u, y - u * 4 );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case '5':
			glRectd( x, y, x + u, y - u * 4 );
			glRectd( x + u * 3, y - u * 3, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x, y - s + u, x + u * 3, y - s );
			break;

		case '6':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y - u * 3, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case '7':
			glRectd( x, y, x + u * 4, y - u );
			glRectd( x + u * 3, y - u, x + u * 4, y - s );
			break;

		case '8':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case '9':
			glRectd( x, y, x + u, y - u* 4 );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'A':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'B':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 3 );
			glRectd( x + u * 3, y - u * 4, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case 'C':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u, y - s + u, x + u * 4, y - s );
			break;

		case 'D':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y - u, x + u * 4, y - s + u );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case 'E':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u, y - u * 3, x + u * 4, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 4, y - s );
			break;

		case 'F':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u, y - u * 3, x + u * 4, y - u * 4 );
			break;

		case 'G':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y - u * 3, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x + u * 2, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;

		case 'H':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'I':
			glRectd( x + u, y - u, x + u * 2, y - s + u );
			glRectd( x, y, x + u * 3, y - u );
			glRectd( x, y - s + u, x + u * 3, y - s );
			break;

		case 'J':
			glRectd( x, y - s + u * 2, x + u, y - s + u );
			glRectd( x + u * 2, y - u, x + u * 3, y - s + u );
			glRectd( x + u, y, x + u * 4, y - u );
			glRectd( x, y - s + u, x + u * 3, y - s );
			break;

		case 'K':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 3 );
			glRectd( x + u * 3, y - u * 4, x + u * 4, y - s );
			glRectd(x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'L':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u, y - s + u, x + u * 4, y - s );
			break;

		case 'M':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 4, y, x + u * 5, y - s );
			glRectd( x + u, y - u, x + u * 2, y - u * 2 );
			glRectd( x + u * 2, y - u * 2, x + u * 3, y - u * 3 );
			glRectd( x + u * 3, y - u, x + u * 4, y - u * 2 );
			break;

		case 'N':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 4, y, x + u * 5, y - s );
			glRectd( x + u, y - u, x + u * 2, y - u * 3 );
			glRectd( x + u * 2, y - u * 3, x + u * 3, y - s + u * 3 );
			glRectd( x + u * 3, y - s + u * 3, x + u * 4, y - s + u );
			break;

		case 'P':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 4 );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'Q':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			glRectd( x + u * 2, y - s + u * 2, x + u * 3, y - s + u );
			break;

		case 'R':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 3 );
			glRectd( x + u * 3, y - u * 4, x + u * 4, y - s );
			glRectd( x + u, y, x + u * 3, y - u );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'S':
			glRectd( x, y, x + u * 4, y - u );
			glRectd( x, y - u, x + u, y - u * 3 );
			glRectd( x, y - u * 3, x + u * 4, y - u * 4 );
			glRectd( x + u * 3, y - u * 4, x + u * 4, y - s + u );
			glRectd( x, y - s + u, x + u * 4, y - s );
			break;

		case 'T':
			glRectd( x + u * 2, y - u, x + u * 3, y - s );
			glRectd( x, y, x + u * 5, y - u );
			break;

		case 'U':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y - s + u, x + u * 3, y - s );
			break;
			
		case 'V':
			glRectd( x, y, x + u, y - s + u * 2 );
			glRectd( x + u * 3, y, x + u * 4, y - s + u );
			glRectd( x + u, y - s + u * 2, x + u * 2, y - s + u );
			glRectd( x + u * 2, y - s + u, x + u * 3, y - s );
			break;

		case 'W':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u * 2, y - u * 3, x + u * 3, y - s + u );
			glRectd( x + u * 4, y, x + u * 5, y - s );
			glRectd( x + u, y - s + u, x + u * 4, y - s );
			break;

		case 'X':
			glRectd( x, y, x + u, y - u * 4 );
			glRectd( x, y - u * 5, x + u, y - s );
			glRectd( x + u * 3, y, x + u * 4, y - u * 3 );
			glRectd( x + u * 3, y - u * 4, x + u * 4, y - s );
			glRectd( x + u, y - u * 4, x + u * 2, y - u * 5 );
			glRectd( x + u * 2, y - u * 3, x + u * 3, y - u * 4 );
			break;

		case 'Y':
			glRectd( x, y, x + u, y - u * 4 );
			glRectd( x + u * 3, y, x + u * 4, y - s );
			glRectd( x + u, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x, y - s + u, x + u * 3, y - s );
			break;

		case 'Z':
			glRectd( x, y - s + u * 2, x + u, y - s + u );
			glRectd( x + u, y - s / 2, x + u * 2, y - s + u * 2 );
			glRectd( x + u * 2, y - u * 2, x + u * 3, y - s / 2 );
			glRectd( x + u * 3, y - u, x + u * 4, y - u * 2 );
			glRectd( x, y, x + u * 4, y - u );
			glRectd( x, y - s + u, x + u * 4, y - s );
			break;

		case '.':
			glRectd( x, y - s + u, x + u, y - s );
			break;

		case ',':
			glRectd( x, y - s + u, x + u, y - s - u );
			break;

		case '!':
			glRectd( x, y, x + u, y - s + u * 2 );
			glRectd( x, y - s + u, x + u, y - s );
			break;

		case ':':
			glRectd( x, y - u * 2, x + u, y - u * 3 );
			glRectd( x, y - s + u, x + u, y - s );
			break;

		case ';':
			glRectd( x, y - u * 2, x + u, y - u * 3 );
			glRectd( x, y - s + u, x + u, y - s - u );
			break;

		case '|':
			glRectd( x, y + u, x + u, y - s - u );
			break;

		case '\'':
			glRectd( x, y, x + u, y - u * 2 );
			break;

		case '?':
			glRectd( x, y, x + u, y - u );
			glRectd( x, y - u * 3, x + u, y - s + u * 2 );
			glRectd( x, y - s + u, x + u, y - s );
			glRectd( x + u, y, x + u * 2, y - u * 4 );
			break;

		case '(':
			glRectd( x, y - u, x + u, y - s + u );
			glRectd( x + u, y, x + u * 2, y - u );
			glRectd( x + u, y - s + u, x + u * 2, y - s );
			break;
			
		case ')':
			glRectd( x, y, x + u, y - u );
			glRectd( x, y - s + u, x + u, y - s );
			glRectd( x + u, y - u, x + u * 2, y - s + u );
			break;

		case '[':
			glRectd( x, y, x + u, y - s );
			glRectd( x + u, y, x + u * 2, y - u );
			glRectd( x + u, y - s + u, x + u * 2, y - s );
			break;

		case ']':
			glRectd( x, y, x + u, y - u );
			glRectd( x, y - s + u, x + u, y - s );
			glRectd( x + u, y, x + u * 2, y - s );
			break;

		case '"':
			glRectd( x, y, x + u, y - u * 2 );
			glRectd( x + u * 2, y, x + u * 3, y - u * 2 );
			break;

		case '-':
			glRectd( x, y - u * 4, x + u * 3, y - u * 5 );
			break;

		case '+':
			glRectd( x + u, y - u * 3, x + u * 2, y - u * 4);
			glRectd( x + u, y - u * 5, x + u * 2, y - u * 6);
			glRectd( x, y - u * 4, x + u * 3, y - u * 5 );
			break;

		case '=':
			glRectd( x, y - u * 3, x + u * 3, y - u * 4 );
			glRectd( x, y - u * 5, x + u * 3, y - u * 6 );
			break;

		case '_':
			glRectd( x, y - s + u, x + u * 4, y - s );
			break;

		case '/':
			glRectd( x, y - s + u * 2, x + u, y - s );
			glRectd( x + u, y - s / 2, x + u * 2, y - s + u * 2 );
			glRectd( x + u * 2, y - u * 2, x + u  * 3, y - s / 2 );
			glRectd( x + u * 3, y, x + u * 4, y - u * 2 );
			break;

		case '\\':
			glRectd( x, y, x + u, y - u * 2 );
			glRectd( x + u, y - u * 2, x + u  * 2, y - s / 2 );
			glRectd( x + u * 2, y - s / 2, x + u * 3, y - s + u * 2 );
			glRectd( x + u * 3, y - s + u * 2, x + u * 4, y - s );
			break;

	}
}
