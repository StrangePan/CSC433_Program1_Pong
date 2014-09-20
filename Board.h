#ifndef _BOARD_H_
#define _BOARD_H_

#include "Drawable.h"

class Board : Drawable
{
	public:
		int center_x;
		int center_y;
		int width;
		int height;

		Board(int x, int y, int width, int height);
		void draw();
};

#endif