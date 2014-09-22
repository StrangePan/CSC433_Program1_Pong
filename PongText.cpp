#include "PongText.h"

PongText::PongText(string text, double x, double y, double size, int align = 1) :
		text(text), x(x), y(y), size(size), align(align)
{ }

PongText::~PongText()
{ }

void PongText::setText(string text)
{ }

void PongText::setPosition(double x, double y)
{ }

void PongText::setSize(double size)
{ }

void PongText::setAlignment(int align)
{ }

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
	int x_off = 0;
	int y_off = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n')
		{
			x_off = 0;
			y_off++;
		}
		else if (text[i] == ' ')
		{
			x_off += 2;
		}
		else
		{
			draw_char(text[i], x + x_off / 8.0, y + y_off * 10.0 / 8.0, size);
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
		case '!':
		case ',':
		case ':':
		case ';':
		case '|':
		case '\'':
			return 1;

		case '?':
		case '`':
			return 2;

		case 'I':
		case 'X':
		case '"':
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
		case 'Y':
		case 'Z':
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
	for (int i = 0; i <= text.size(); i++)
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
