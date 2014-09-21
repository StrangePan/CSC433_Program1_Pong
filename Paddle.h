#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Drawable.h"


class Paddle : public Drawable
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
		void draw();
};

#endif