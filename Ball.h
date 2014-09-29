#ifndef _BALL_H_
#define _BALL_H_

class Ball;

#include <cmath>
#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

class Ball : public Drawable, public Steppable
{
	public:
		double center_x;
		double center_y;
		int width;
		double x_velocity;
		double y_velocity;
		PongGame* game;

		Ball(PongGame* game, double x, double y, int width, double x_velocity, double y_velocity);
		void step();
		void draw();
};

#endif