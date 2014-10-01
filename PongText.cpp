/***************************************************************************//**
 * @file File containing the implementation of the PongText class.
 *
 * @brief Contains the implementation for the PongText class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "PongText.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The constructor. Initializes variables and classes.
*******************************************************************************/
PongText::PongText(double x, double y, double size, string text, int align) :
		x(x), y(y), size(size), text(text), align(align)
{
	if (align < -1) this -> align = -1;
	if (align > 1) this -> align = 1;
	calc_size();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The destructor. Frees up dynamic memory.
*******************************************************************************/
PongText::~PongText()
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Function to change the displaye text.
 *
 * @param[in]	text - The new text to display.
*******************************************************************************/
void PongText::setText(string text)
{
	this -> text = text;
	calc_size();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Changes the position of text
 *
 * @param[in]	x - New x coordinate
 * @param[in]	y - New y coordinate
*******************************************************************************/
void PongText::setPosition(double x, double y)
{
	this -> x = x;
	this -> y = y;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Changes the hight of each individual letter
 *
 * @param[in]	size - New height in pixels of the text
*******************************************************************************/
void PongText::setSize(double size)
{
	this -> size = size;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Changes the alignment of text
 *
 * @param[in]	align - Sets the alignment of the text. 1 is left align, 0
 *		is center, -1 is right align
*******************************************************************************/
void PongText::setAlignment(int align)
{
	this -> align = ( align < 0 ? -1 : align > 0 ? 1 : 0 );
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the width of the text
 *
 * @returns The width in pixels
*******************************************************************************/
double PongText::getWidth()
{
	return size / 8 * width;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the height of the text
 *
 * @returns The height in pixels
*******************************************************************************/
double PongText::getHeight()
{
	return size * 10 / 8 * height;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Draws the text
*******************************************************************************/
void PongText::draw()
{
	double x;
	double y = this -> y;
	int x_off = 0;
	int y_off = 0;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		// If new line, calculate line starting point
		if (x_off == 0)
		{
			// Calculate width of current line
			int w = 0;
			for (unsigned int j = i; j < text.size() && text[j] != '\n'; j++)
			{
				w += char_width(text[j]) + 1;
			}
			if (w > 0) w--; // fix off-by-one error

			switch (align)
			{
				default:
				case 1:		// left align
					x = this -> x;
					break;

				case 0:		// center align
					x = this -> x - (w * size / 8.0) / 2.0;
					break;

				case -1:	// right align
					x = this->x - (w * size / 8.0);
					break;
			}
		}

		if (text[i] == '\n')	// Special case for new line
		{
			x_off = 0;
			y_off++;
		}
		else if (text[i] == ' ')	// Special case for space
		{
			x_off += (x_off == 0 ? 3 : 2);
		}
		else
		{
			draw_char(text[i], x + x_off * size / 8.0, y + y_off * size * 10.0 / 8.0, size);
			x_off += char_width(text[i]) + 1;
		}
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the width of a single character
 *
 * @returns The width in units of the individual character
*******************************************************************************/
int PongText::char_width(char c)
{
	switch (toupper(c))
	{
		default:
			return 0;

		case '1':
		case ' ':
		case '.':
		case ',':
		case '!':
		case ':':
		case ';':
		case '|':
		case '\'':
			return 1;

		case '?':
		case '(':
		case ')':
		case '[':
		case ']':
			return 2;

		case 'I':
		case '"':
		case '-':
		case '+':
		case '=':
			return 3;

		case '0':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'J':
		case 'K':
		case 'L':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'U':
		case 'V':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case '/':
		case '\\':
			return 4;
			
		case 'M':
		case 'N':
		case 'T':
		case 'W':
			return 5;
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the height of a single character
 *
 * @returns The height of the character
*******************************************************************************/
int PongText::char_height(char c)
{
	return 8;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Calculates the size of the text field
*******************************************************************************/
void PongText::calc_size()
{
	int w = 0;
	int h = 0;
	width = 0;
	height = 0;
	for (unsigned int i = 0; i <= text.size(); i++)
	{
		if (i == text.size() || text[i] == '\n')
		{
			if (w > width)
			{
				width = w;
			}
			w = 0;
		}
		else
		{
			if (w == 0)
			{
				h++;
			}
			else
			{
				w++;
			}
			w += char_width(text[i]);
		}
	}
	height = h;
}
