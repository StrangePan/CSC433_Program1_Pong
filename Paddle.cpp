#include "Paddle.h"

Paddle::Paddle(int x, int y, int width, int height) :
		center_x(x), center_y(y), width(width), height(height),
		top(true), bottom(true), right(true), left(true)
{ }

void Paddle::draw()
{
	glColor3f( 1.0, 1.0, 1.0 );
	glRectf( center_x - (width / 2), center_y -(height / 2), center_x
		+ (width / 2), center_y + (height / 2 ) );
}