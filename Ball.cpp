#include "Ball.h"

Ball::Ball(int x, int y, int width, double x_velocity, double y_velocity) : 
		center_x(x), center_y(y), width(width),
		x_velocity(x_velocity), y_velocity(y_velocity)
{ }

void Ball::draw( )
{
	float radius = float(width) / 2.0;   // stretch circle into ellipse
    glColor3f( 1.0, 0.0, 1.0 );
    glPushMatrix();
    glTranslatef( center_x, center_y, 0 );
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

	if( center_x == 600 - width/2 || center_x == 0 + width/2 )
	{
		x_velocity *= -1;
	}
	if( center_y == 300 - width/2 || center_y == 0 + width/2 )
	{
		y_velocity *= -1;
	}

}