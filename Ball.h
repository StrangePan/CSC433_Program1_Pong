#ifndef _BALL_H_
#define _BALL_H_

class Ball;

#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

class Ball : public Drawable, public Steppable
{
	public:
		int center_x;
		int center_y;
		int width;
		double x_velocity;
		double y_velocity;
		PongGame* game;

		Ball(PongGame* game, int x, int y, int width, double x_velocity, double y_velocity);
		void step();
		void draw();
};

#endif