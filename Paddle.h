#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle;

#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

class Paddle : public Drawable, public Steppable
{
	public:
		int height;
		int width;
		int center_x;
		int center_y;
		PongGame* game;
		
		Paddle(PongGame* game, int x, int y, int width, int height);
		void step();

		int getX();
		int getY();
		int getWidth();
		int getHeight();

		void draw();
};

#endif