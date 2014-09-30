#include "Paddle.h"

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * Creates a paddle with a field that it can be in, its possition, and size
 * 
 * 
 * 
 * @param[in]      PongGame* game - Instance of the PongGame class that is
 *						in charge of the paddle
 * @param[in]      double x - the x coordinate of the center of the paddle
 * @param[in]      double y - the y coordinate of the center of the paddle
 * @param[in]      int	width - the total width of the paddle
 * @param[in]      int height - the total height of the paddle
 * @param[in]      int maxx	- the maximum x coordinate for the paddle
 * @param[in]      int minx - the minimum x coordinate for the paddle
 * @param[in]      int maxy	- the maximum y coordinate for the paddle
 * @param[in]      int miny - the minimum y coordinate for the paddle
 *****************************************************************************/
Paddle::Paddle(PongGame* game, double x, double y, int width, int height, int maxx, int minx, int maxy, int miny) :
		game(game), center_x(x), center_y(y), width(width), height(height),
		up(false), down(false), left(false), right(false), maxx(maxx), minx(minx), maxy(maxy), miny(miny),
		horizontal_paddle_speed(4), vertical_paddle_speed(4)
{ }

/**************************************************************************//**
 * @author Daniel Andrus, Johnathan Ackerman
 * 
 * @par Description: 
 * Draws the paddle with the help of the drawable class
 * 
 *****************************************************************************/
void Paddle::draw()
{
	glColor3f( 1.0, 1.0, 1.0 ); // sets color to white
	//draws paddle
	glRectd( center_x - (width / 2), center_y -(height / 2), center_x
		+ (width / 2), center_y + (height / 2 ) );
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Acekerman
 * 
 * @par Description: 
 * Moves the paddle accros the screen
 *****************************************************************************/
void Paddle::step( )
{
	//uses booliens set by keyboard input
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

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * retrieves the x coordinate of the paddles
 * 
 * @returns x - the horizontal location of the paddle
 *****************************************************************************/
double Paddle::getX()
{
	return center_x;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * retrieves the y coordinate of the paddles
 * 
 * @returns y - the vertical location of the paddle
 *****************************************************************************/
double Paddle::getY()
{
	return center_y;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
int Paddle::getWidth()
{
	return width;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * retrieves total height of the paddles
 * 
 * @returns x - the current height of the paddle
 *****************************************************************************/
int Paddle::getHeight()
{
	return height;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * changes the paddles speed and moves the padle vertically
 * 
 * 
 * @param[in]      double speed - the movement of the paddle
 *****************************************************************************/
void Paddle::verticalMotion( double speed )
{
	//sets speed
	if (speed > vertical_paddle_speed)
	{
		speed = vertical_paddle_speed;
	}
	if (speed < -vertical_paddle_speed)
	{
		speed = -vertical_paddle_speed;
	}

	//moves paddle
	center_y += speed;

	//makes sure paddle is in bounds of height
	if (center_y + height / 2 > maxy)
	{
		center_y = maxy - height / 2;
	}
	if (center_y - height / 2 < miny)
	{
		center_y = miny + height / 2;
	}
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * changes the paddles speed and moves the padle horizontally
 * 
 * 
 * @param[in]      double speed - the amount of movement for the paddle
 *****************************************************************************/
void Paddle::horizontalMotion( double speed )
{
	//changes speed
	if (speed > horizontal_paddle_speed)
	{
		speed = horizontal_paddle_speed;
	}
	if (speed < -horizontal_paddle_speed)
	{
		speed = -horizontal_paddle_speed;
	}
	//moves horizontally
	center_x += speed;

	//makes sure paddle is in its boundaries
	if (center_x + width / 2 > maxx)
	{
		center_x = maxx - width / 2;
	}
	if (center_x - width / 2 < minx)
	{
		center_x = minx + width / 2;
	}
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * sets the maximum value for paddle speed horizonatally and vertically
 * 
 * 
 * @param[in]      double horizSpeed - the max speed of a paddle horizontally
 * @param[in]      double vertSpeed - the max speed of a paddle vertically
 *****************************************************************************/
void Paddle::change_max_paddle_speed( double horizSpeed, double vertSpeed )
{
	//sets speed
	horizontal_paddle_speed = abs(horizSpeed);
	vertical_paddle_speed = abs(vertSpeed);

	//makes speed at least 1
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

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: 
 * retrieves the height of the paddle
 * 
 * 
 * @param[in]      int height - the total height of the paddle
 *****************************************************************************/
void Paddle::setHeight(int height)
{
	this -> height = height;
}

