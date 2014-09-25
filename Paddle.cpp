#include "Paddle.h"

Paddle::Paddle(PongGame* game, double x, double y, int width, int height, int maxx, int minx, int maxy, int miny) :
		game(game), center_x(x), center_y(y), width(width), height(height),
		up(false), down(false), left(false), right(false), maxx(maxx), minx(minx), maxy(maxy), miny(miny),
		horizontal_paddle_speed(4), vertical_paddle_speed(4)
{ }

void Paddle::draw()
{
	glColor3f( 1.0, 1.0, 1.0 );
	glRectf( center_x - (width / 2), center_y -(height / 2), center_x
		+ (width / 2), center_y + (height / 2 ) );
}

void Paddle::step( )
{
	if( up )
	{
		verticalMotion( vertical_paddle_speed );
	}
	if( down )
	{
		verticalMotion( -vertical_paddle_speed );
	}
	if( left )
	{
		horizontalMotion( -horizontal_paddle_speed );
	}
	if( right )
	{
		horizontalMotion( horizontal_paddle_speed );
	}
};

double Paddle::getX()
{
	return center_x;
}
double Paddle::getY()
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

void Paddle::verticalMotion( double speed )
{
	if (speed > vertical_paddle_speed)
	{
		speed = vertical_paddle_speed;
	}
	if (speed < -vertical_paddle_speed)
	{
		speed = -vertical_paddle_speed;
	}
	center_y += speed;
	if (center_y + height / 2 > maxy)
	{
		center_y = maxy - height / 2;
	}
	if (center_y - height / 2 < miny)
	{
		center_y = miny + height / 2;
	}
}

void Paddle::horizontalMotion( double speed )
{
	if (speed > horizontal_paddle_speed)
	{
		speed = horizontal_paddle_speed;
	}
	if (speed < -horizontal_paddle_speed)
	{
		speed = -horizontal_paddle_speed;
	}
	center_x += speed;
	if (center_x + width / 2 > maxx)
	{
		center_x = maxx - width / 2;
	}
	if (center_x - width / 2 < minx)
	{
		center_x = minx + width / 2;
	}
}

void Paddle::change_max_paddle_speed( double horizSpeed, double vertSpeed )
{
	horizontal_paddle_speed = abs(horizSpeed);
	vertical_paddle_speed = abs(vertSpeed);

	if (horizontal_paddle_speed < 1)
	{
		horizontal_paddle_speed = 1;
	}
	if (vertical_paddle_speed < 1)
	{
		vertical_paddle_speed = 1;
	}
	
	return;
}

void Paddle::setHeight(int height)
{
	this -> height = height;
}

