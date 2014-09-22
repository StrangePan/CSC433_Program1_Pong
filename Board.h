#ifndef _BOARD_H_
#define _BOARD_H_

class Board;

#include <string>
#include "Drawable.h"
#include "Pong.h"
#include "PongText.h"

using namespace std;

class Board : public Drawable
{
	public:
		int x;
		int y;
		int width;
		int height;
		int border;
		PongText left_text;
		PongText right_text;

		Board(int x, int y, int width, int height, int border);
		~Board();
		void setLeftText(string text);
		void setRightText(string text);

		void draw();
};

#endif