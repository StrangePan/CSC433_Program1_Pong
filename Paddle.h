#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Drawable.h"
#include "Steppable.h"

class Paddle : public Drawable, public Steppable
{
	public:
		int height;
		int width;
		int center_x;
		int center_y;
		bool top;
		bool bottom;
		bool right;
		bool left;
		
		Paddle(int x, int y, int width, int height);
		void step();
		void draw();
};

#endif