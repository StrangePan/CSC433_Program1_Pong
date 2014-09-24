#include "Paddle.h"

Paddle::Paddle(PongGame* game, int x, int y, int width, int height, int maxx, int minx, int maxy, int miny) :
		game(game), center_x(x), center_y(y), width(width), height(height),
		up(false), down(false), left(false), right(false), maxx(maxx), minx(minx), maxy(maxy), miny(miny)
{ }

void Paddle::draw()
{
	glColor3f( 1.0, 1.0, 1.0 );
	glRecti( center_x - (width / 2), center_y -(height / 2), center_x
		+ (width / 2), center_y + (height / 2 ) );
}

void Paddle::step()
{
	if( up || down )
	{
		verticalMotion( 3 );
	}
	if( left || right )
	{
		horizontalMotion( 2 );
	}
};

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

void Paddle::verticalMotion( int speed )
{
	if (up)
	{
		center_y += speed;
		if (center_y + height / 2 > maxy)
		{
			center_y = maxy - height / 2;
		}
	}
	if (down)
	{
		center_y -= speed;
		if (center_y - height / 2 < miny)
		{
			center_y = miny + height / 2;
		}
	}
}

void Paddle::horizontalMotion( int speed )
{
	if (right)
	{
		center_x += speed;
		if (center_x + width / 2 > maxx)
		{
			center_x = maxx - width / 2;
		}
	}
	if (left)
	{
		center_x -= speed;
		if (center_x - width / 2 < minx)
		{
			center_x = minx + width / 2;
		}
	}
}
