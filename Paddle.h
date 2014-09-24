#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle;

#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

class Paddle : public Drawable, public Steppable
{
	private:
		int height;
		int width;
		int center_x;
		int center_y;
		int maxx;
		int minx;
		int maxy;
		int miny;
		PongGame* game;
	
	public:
		bool up;
		bool down;
		bool left;
		bool right;
		
		Paddle(PongGame* game, int x, int y, int width, int height, int maxx, int minx, int maxy, int miny);
		void step();
		void verticalMotion( int speed );
		void horizontalMotion( int speed);

		int getX();
		int getY();
		int getWidth();
		int getHeight();

		void draw();
};

#endif