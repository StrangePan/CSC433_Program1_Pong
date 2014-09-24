#include "Ball.h"

Ball::Ball(PongGame* game, double x, double y, int width, double x_velocity, double y_velocity) : 
		game(game), center_x(x), center_y(y), width(width),
		x_velocity(x_velocity), y_velocity(y_velocity)
{ }

void Ball::draw( )
{
	float radius = (float) (width / 2.0);   // stretch circle into ellipse
    glColor3f( 1.0, 0.0, 1.0 );
    glPushMatrix();
    glTranslated( center_x, center_y, 0 );
    //glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glPopMatrix();
}

void Ball::step( )
{	
	center_x += x_velocity;
	center_y += y_velocity;

	// Upper/lower walls
	if (center_y >= game->getBoard()->getY() + game->getBoard()->getHeight() - width / 2)
	{
		y_velocity = -abs(y_velocity);
	}
	if (center_y <= game->getBoard()->getY() + width / 2)
	{
		y_velocity = abs(y_velocity);
	}

	/*
	if ( center_x >= game->getBoard()->getX() + game->getBoard()->getWidth() - width / 2 )
	{
		x_velocity = -abs(x_velocity);
	}
	if ( center_x <= game -> getBoard() -> getX() + width/2 )
	{
		x_velocity = abs(x_velocity);
	}
	*/

	// Paddles
	if (x_velocity > 0)
	{
		if (center_x >= game->getRightPaddle()->getX() - game->getRightPaddle()->getWidth() / 2 - width / 2
			&& center_x <= game->getRightPaddle()->getX() - width / 2
			&& center_y - width / 2 < game->getRightPaddle()->getY() + game->getRightPaddle()->getHeight() / 2
			&& center_y + width / 2 > game->getRightPaddle()->getY() - game->getRightPaddle()->getHeight() / 2)
		{
			x_velocity = -abs(x_velocity);
			y_velocity = (center_y - game->getRightPaddle()->getY()) / (game->getRightPaddle()->getHeight() / 4.0);
		}
		else if (center_x - width / 2 > game->getBoard()->getX() + game->getBoard()->getWidth())
		{
			game -> scoreRight(); // TODO Score left
		}
	}
	else
	{
		if (center_x <= game->getLeftPaddle()->getX() + game->getLeftPaddle()->getWidth() / 2 + width / 2
			&& center_x >= game->getLeftPaddle()->getX() + width / 2
			&& center_y - width / 2 < game->getLeftPaddle()->getY() + game->getLeftPaddle()->getHeight() / 2
			&& center_y + width / 2 > game->getLeftPaddle()->getY() - game->getLeftPaddle()->getHeight() / 2)
		{
			x_velocity = abs(x_velocity);
			y_velocity = (center_y - game->getLeftPaddle()->getY()) / (game->getLeftPaddle()->getHeight() / 4.0);
		}
		else if (center_x + width / 2 < game->getBoard()->getX())
		{
			game -> scoreLeft(); // TODO Score right
		}
	}
	

}
