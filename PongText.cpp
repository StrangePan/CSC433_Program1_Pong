#include "PongText.h"

PongText::PongText(double x, double y, double size, string text, int align) :
		x(x), y(y), size(size), text(text), align(align)
{
	if (align < -1) this -> align = -1;
	if (align > 1) this -> align = 1;
	calc_size();
}

PongText::~PongText()
{ }

void PongText::setText(string text)
{
	this -> text = text;
	calc_size();
}

void PongText::setPosition(double x, double y)
{
	this -> x = x;
	this -> y = y;
}

void PongText::setSize(double size)
{
	this -> size = size;
}

void PongText::setAlignment(int align)
{
	this -> align = ( align < 0 ? -1 : align > 0 ? 1 : 0 );
}

double PongText::getWidth()
{
	return size / 8 * width;
}

double PongText::getHeight()
{
	return size * 10 / 8 * height;
}

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

int PongText::char_height(char c)
{
	return 8;
}

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
