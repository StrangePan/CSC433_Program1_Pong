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
 * 
 *****************************************************************************/
Ball::Ball(PongGame* game, double x, double y, int width, 
						double x_velocity, double y_velocity) : 
		game(game), center_x(x), center_y(y), width(width),
		x_velocity(x_velocity), y_velocity(y_velocity)
{ }

/**************************************************************************//** 
 * @author Johnathan Ackerman, Daniel Andrus
 * 
 * @par Description: Draws the ball with class information
 * 
 *****************************************************************************/
void Ball::draw( )
{

	//Draws the ball with freeGlut
	float radius = (float) (width / 2.0);
    glColor3f( 1.0, 0.0, 1.0 );
    glPushMatrix();
    glTranslated( center_x, center_y, 0 );
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glPopMatrix();
}

/**************************************************************************//** 
 * @author Johnathan Ackerman
 * 
 * @par Description: moves the ball across the game grid
 * 
 *****************************************************************************/
void Ball::step( )
{	
	//changes possition based on velocity
	center_x += x_velocity;
	center_y += y_velocity;

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

	// Paddles
	if (x_velocity > 0) //Right paddle
	{
		if (center_x >= game->getRightPaddle()->getX()
					- game->getRightPaddle()->getWidth() / 2 - width / 2
			&& center_x <= game->getRightPaddle()->getX() - width / 2
			&& center_y - width / 2 < game->getRightPaddle()->getY()
					+ game->getRightPaddle()->getHeight() / 2
			&& center_y + width / 2 > game->getRightPaddle()->getY()
					- game->getRightPaddle()->getHeight() / 2)
		{
			x_velocity = -abs(x_velocity);
			y_velocity = (center_y - game->getRightPaddle()->getY())
					/ (game->getRightPaddle()->getHeight() / 12.0);
			game->ballHit(true);
		}
		else if (center_x - width / 2 > game->getBoard()->getX()
					+ game->getBoard()->getWidth()) //got passed right paddle
		{
			game -> scoreLeft();
		}
	}
	else // left paddle
	{
		if (center_x <= game->getLeftPaddle()->getX()
					+ game->getLeftPaddle()->getWidth() / 2 + width / 2
			&& center_x >= game->getLeftPaddle()->getX() + width / 2
			&& center_y - width / 2 < game->getLeftPaddle()->getY()
					+ game->getLeftPaddle()->getHeight() / 2
			&& center_y + width / 2 > game->getLeftPaddle()->getY()
					- game->getLeftPaddle()->getHeight() / 2)
		{
			x_velocity = abs(x_velocity);
			y_velocity = (center_y - game->getLeftPaddle()->getY()) 
						/ (game->getLeftPaddle()->getHeight() / 12.0); 
			game->ballHit(false);
		}
		//passed the paddle
		else if (center_x + width / 2 < game->getBoard()->getX())
		{
			game -> scoreRight();
		}
	}
	

}
