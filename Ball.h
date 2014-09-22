#ifndef _BALL_H_
#define _BALL_H_

#include "Drawable.h"
#include "Steppable.h"

class Ball : public Drawable, public Steppable
{
	public:
		int center_x;
		int center_y;
		int width;
		double x_velocity;
		double y_velocity;

		Ball(int x, int y, int width, double x_velocity, double y_velocity);
		void step();
		void draw();
};

#endif