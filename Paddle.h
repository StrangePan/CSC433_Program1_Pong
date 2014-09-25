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
		double center_x;
		double center_y;
		int maxx;
		int minx;
		int maxy;
		int miny;
		double vertical_paddle_speed;
		double horizontal_paddle_speed;
		PongGame* game;
	
	public:
		bool up;
		bool down;
		bool left;
		bool right;
		
		Paddle(PongGame* game, double x, double y, int width, int height, int maxx, int minx, int maxy, int miny);
		void step();
		void verticalMotion( double speed );
		void horizontalMotion( double speed);
		void change_max_paddle_speed( double horizSpeed, double vertSpeed );

		double getX();
		double getY();
		int getWidth();
		int getHeight();

		void draw();
};

#endif