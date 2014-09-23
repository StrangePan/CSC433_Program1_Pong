#include "Ball.h"

Ball::Ball(PongGame* game, int x, int y, int width, double x_velocity, double y_velocity) : 
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
	center_x += (int) x_velocity;
	center_y += (int) y_velocity;

	if( center_x >= game -> getBoard() -> getWidth() - width/2 || center_x <= 0 + width/2 )
	{
		x_velocity *= -1;
	}
	if( center_y >= game -> getBoard() -> getHeight() - width/2 || center_y <= 0 + width/2 )
	{
		y_velocity *= -1;
	}

	//paddle walls
	if( ( center_x == ( game -> getLeftPaddle() -> getX() + ( width / 2 ) +
		( game -> getLeftPaddle() -> getWidth() / 2 ) ) ||
		center_x == (game -> getLeftPaddle() -> getX() - ( width / 2 ) -
		( game -> getLeftPaddle() -> getWidth() / 2 )) ) && 
		( center_y < ( game -> getLeftPaddle() -> getY() + 
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ) &&
		( center_y > ( game -> getLeftPaddle() -> getY() -
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ) )
	{
		x_velocity *= -1;
	}

	if( center_x == ( game -> getRightPaddle() -> getX() + ( width / 2 ) +
		( game -> getRightPaddle() -> getWidth() / 2 ) ) ||
		center_x == ( game -> getRightPaddle() -> getX() - ( width / 2 ) -
		( game -> getRightPaddle() -> getWidth() / 2 ) ) && 
		( center_y < ( game -> getRightPaddle() -> getY() + 
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ) &&
		( center_y > ( game -> getRightPaddle() -> getY() -
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ) )
	{
		x_velocity *= -1;
	}
	//top and bottom
	if( ( center_y == ( game -> getLeftPaddle() -> getY() + ( width / 2 ) +
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ||
		center_y == ( game -> getLeftPaddle() -> getY() - ( width / 2 ) -
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ) &&
		( (center_x < game -> getLeftPaddle() -> getX() +
		( game -> getLeftPaddle() -> getWidth() / 4 ) )&&
		(center_x > game -> getLeftPaddle() -> getX() -
		( game -> getLeftPaddle() -> getWidth() /2 ) ) ) )
	{
		y_velocity *= -1;
	}

	if( ( center_y == ( game -> getRightPaddle() -> getY() + ( width / 2 ) +
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ||
		center_y == ( game -> getRightPaddle() -> getY() - ( width / 2 ) -
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ) &&
		( (center_x > game -> getRightPaddle() -> getX() -
		( game -> getRightPaddle() -> getWidth() / 4 ) )&&
		(center_x < game -> getRightPaddle() -> getX() +
		( game -> getRightPaddle() -> getWidth() /2 ) ) ) )
	{
		y_velocity *= -1;
	}
	//corners
	if( ( center_y == ( game -> getLeftPaddle() -> getY() + ( width / 2 ) +
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ||
		center_y == ( game -> getLeftPaddle() -> getY() - ( width / 2 ) -
		( game -> getLeftPaddle() -> getHeight() / 2 ) ) ) &&
		( (center_x > game -> getLeftPaddle() -> getX() +
		( game -> getLeftPaddle() -> getWidth() / 4 ) )&&
		(center_x < game -> getLeftPaddle() -> getX() +
		(( game -> getLeftPaddle() -> getWidth() /2) + (width / 2) ) ) ) )
	{
		x_velocity *= -1;
		y_velocity *= -1;
	}

	if( ( center_y == ( game -> getRightPaddle() -> getY() + ( width / 2 ) +
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ||
		center_y == ( game -> getRightPaddle() -> getY() - ( width / 2 ) -
		( game -> getRightPaddle() -> getHeight() / 2 ) ) ) &&
		( (center_x < game -> getRightPaddle() -> getX() -
		( game -> getRightPaddle() -> getWidth() / 4 ) )&&
		(center_x > game -> getRightPaddle() -> getX() -
		( ( game -> getRightPaddle() -> getWidth() /2 ) - (width / 2) ) ) ) )
	{
		x_velocity *= -1;
		y_velocity *= -1;
	}

}