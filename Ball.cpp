/***************************************************************************//**
 * @file File containing the implementation for the Ball class.
 *
 * @brief Contains the implementation for the Ball class.
*******************************************************************************/
#include "Ball.h"

/**************************************************************************//** 
 * @author Johnathan Ackerman, Daniel Andrus
 * 
 * @par Description: Constructor, Creates a Ball
 * 
 * @param[in]	   PongGame* game - Instance of the commanding class
 * @param[in]	   double x - x coordinate on the game grid
 * @param[in]	   double y - y coordinate on the game grid
 * @param[in]	   double width - radious of the ball
 * @param[in]	   double x_velocity - speed the ball is moving in the x 
 *						direction
 * @param[in]	   double y_velocity - velocity in the y vector
 *****************************************************************************/
Ball::Ball(PongGame* game, double x, double y, int width, 
						double x_velocity, double y_velocity) : 
		game(game), center_x(x), center_y(y), width(width),
		x_velocity(x_velocity), y_velocity(y_velocity), s_velocity(1.0)
{ }

/**************************************************************************//** 
 * @author Johnathan Ackerman
 * 
 * @par Description: moves the ball across the game grid
 *****************************************************************************/
void Ball::step( )
{	
	//changes possition based on velocity
	center_x += x_velocity * s_velocity;
	center_y += y_velocity * s_velocity;

	// Upper/lower wall reflections
	if (center_y >= game->getBoard()->getY() + 
				game->getBoard()->getHeight() - width / 2)
	{
		y_velocity = -abs(y_velocity);
	}
	if (center_y <= game->getBoard()->getY() + width / 2)
	{
		y_velocity = abs(y_velocity);
	}

	// Check collision with paddles
	if (x_velocity > 0) //Right paddle
	{
		double left_bound = game->getRightPaddle()->getX()
							- game->getRightPaddle()->getWidth()/2;
		double right_bound = game->getRightPaddle()->getX()
							- game->getRightPaddle()->getWidth()/2
							+ x_velocity * s_velocity;
		double top_bound = game->getRightPaddle()->getY()
							+ game->getRightPaddle()->getHeight() / 2;
		double bot_bound = game->getRightPaddle()->getY()
							- game->getRightPaddle()->getHeight() / 2;
		if (center_x + width / 2 >= left_bound
			&& center_x + width / 2 <= right_bound
			&& center_y + width / 2 >= bot_bound
			&& center_y - width / 2 <= top_bound)
		{
			// Move to contact with paddle
			center_x = left_bound - width / 2;

			// Start moving left
			x_velocity = -abs(x_velocity);

			// Adjust y velocity
			y_velocity += (center_y - game->getRightPaddle()->getY())
					/ (game->getRightPaddle()->getHeight() / 12.0);

			// Govern y_velocity speed, lest we lose the ball!
			if (y_velocity > 10.0) y_velocity = 10.0;
			if (y_velocity < -10.0) y_velocity = -10.0;

			// Let game know that a collision has happened
			game->ballHit(true);
		}

		// Passed the paddle and off the board!
		else if (center_x - width / 2 > game->getBoard()->getX()
							+ game->getBoard()->getWidth())
		{
			game -> scoreLeft();
		}
	}
	else // left paddle
	{
		double left_bound = game->getLeftPaddle()->getX()
							+ game->getLeftPaddle()->getWidth()/2
							+ x_velocity * s_velocity;
		double right_bound = game->getLeftPaddle()->getX()
							+ game->getLeftPaddle()->getWidth() / 2;
		double top_bound = game->getLeftPaddle()->getY()
							+ game->getLeftPaddle()->getHeight() / 2;
		double bot_bound = game->getLeftPaddle()->getY()
							- game->getLeftPaddle()->getHeight() / 2;
		if (center_x - width / 2 >= left_bound
			&& center_x - width / 2 <= right_bound
			&& center_y + width / 2 >= bot_bound
			&& center_y - width / 2 <= top_bound)
		{
			// Move to contact with paddle
			center_x = right_bound + width / 2;

			// Start moving riht
			x_velocity = abs(x_velocity);

			// Adjust y velocity
			y_velocity += (center_y - game->getLeftPaddle()->getY())
				/ (game->getLeftPaddle()->getHeight() / 12.0);

			// Govern y_velocity speed, lest we lose the ball!
			if (y_velocity > 10.0) y_velocity = 10.0;
			if (y_velocity < -10.0) y_velocity = -10.0;

			// Let game know that a collision has happened
			game->ballHit(false);
		}
		
		// Passed the paddle and off the board!
		else if (center_x + width / 2 < game->getBoard()->getX())
		{
			game -> scoreRight();
		}
	}
	

}

/**************************************************************************//** 
 * @author Daniel Andrus
 * 
 * @par Description: Gets the value of the modifier currently being applied to
 *		the ball's speed.
 *
 * @param[in]	s_velocity - The new modifier to apply to the ball. Value must
 *		be a decimal greater than 0.
 *****************************************************************************/
void Ball::setSpeedModifier(double s_velocity)
{
	// Make sure value is valid
	if (s_velocity <= 0.0) return;

	this -> s_velocity = s_velocity;
}

/**************************************************************************//** 
 * @author Daniel Andrus
 * 
 * @par Description: Gets the value of the modifier currently being applied to
 *		the ball's speed.
 *
 * @returns The modifier currently applied to the ball's speed.
 *****************************************************************************/
double Ball::getSpeedModifier()
{
	return s_velocity;
}

/**************************************************************************//** 
 * @author Johnathan Ackerman, Daniel Andrus
 * 
 * @par Description: Draws the ball with class information
 *****************************************************************************/
void Ball::draw( )
{
	float radius = (float) (width / 2.0);
	int slices = (int) radius * 2;
	GLUquadricObj *disk;
	
	// Add blur effect. Don't know how to use transparency, so use dark pink
	glColor3f( 0.25, 0.0, 0.25 );
	glPushMatrix();
	glTranslated( center_x - x_velocity * s_velocity * 2, center_y - y_velocity * s_velocity * 2, 0 );
	disk = gluNewQuadric();
	gluDisk( disk, 0, radius, slices, 1 );
	gluDeleteQuadric( disk );
	glPopMatrix();
	
	glColor3f( 0.5, 0.0, 0.5 );
	glPushMatrix();
	glTranslated( center_x - x_velocity * s_velocity, center_y - y_velocity * s_velocity, 0 );
	disk = gluNewQuadric();
	gluDisk( disk, 0, radius, slices, 1 );
	gluDeleteQuadric( disk );
	glPopMatrix();

	//Draws the ball with freeGlut
    glColor3f( 1.0, 0.0, 1.0 );
    glPushMatrix();
    glTranslated( center_x, center_y, 0 );
    disk = gluNewQuadric();
    gluDisk( disk, 0, radius, slices, 1 );
    gluDeleteQuadric( disk );
    glPopMatrix();
}
