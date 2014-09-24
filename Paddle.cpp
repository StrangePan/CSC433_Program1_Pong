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

int Paddle::getX()
{
	return center_x;
}
int Paddle::getY()
{
	return center_y;
}
int Paddle::getWidth()
{
	return width;
}

int Paddle::getHeight()
{
	return height;
}

void Paddle::moveUp()
{
	if( center_y + height/2 < game -> getBoard() -> getHeight() )
		center_y += 5;
}

void Paddle::moveDown()
{
	if( center_y - height/2 > 0 )
		center_y -= 5;
}

void Paddle::moveRight()
{
	if( center_x + width/2 < ( game -> getBoard() -> getWidth() / 2 ) )
		center_x += 5;
}

void Paddle::moveLeft()
{
	if( center_x - width/2 > 0 )
		center_x -= 5;
}