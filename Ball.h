#ifndef _BALL_H_
#define _BALL_H_

#include "Drawable.h"

class Ball : Drawable
{
	public:
		int center_x;
		int center_y;
		int width;
		int height;
		double x_velocity;
		double y_velocity;

		Ball(int x, int y, int width, int height, double x_velocity, double y_velocity);
		void draw();
};

#endif