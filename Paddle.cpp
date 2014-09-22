#include "Paddle.h"

Paddle::Paddle(PongGame* game, int x, int y, int width, int height) :
		game(game), center_x(x), center_y(y), width(width), height(height)
{ }

void Paddle::draw()
{
	glColor3f( 1.0, 1.0, 1.0 );
	glRectf( center_x - (width / 2), center_y -(height / 2), center_x
		+ (width / 2), center_y + (height / 2 ) );
}

void Paddle::step()
{};