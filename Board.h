#ifndef _BOARD_H_
#define _BOARD_H_

#include "Drawable.h"

class Board : public Drawable
{
	public:
		int x;
		int y;
		int width;
		int height;
		int border;
		int score_1;
		int score_2;

		Board(int x, int y, int width, int height, int border);
		void draw();
};

#endif