#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include "Drawable.h"
using namespace std;

class Board : public Drawable
{
	public:
		int x;
		int y;
		int width;
		int height;
		int border;
		const char *score_1;
		const char *score_2;

		Board(int x, int y, int width, int height, int border);
		void draw();
};

#endif