#ifndef _PONGTEXT_H_
#define _PONGTEXT_H_

class PongText;

#include <string>
#include "Drawable.h"

using namespace std;

class PongText : public Drawable
{
	private:
		string text;
		int align;
		double x;
		double y;
		double size;
		int width;
		int height;

		static int char_width(char c);
		static int char_height(char c);
		static void draw_char(char c, double x, double y, double size);
		void calc_size();

	public:
		PongText(double x, double y, double size, string text = "", int align = 1);
		~PongText();

		void setText(string text);
		void setPosition(double x, double y);
		void setSize(double size);
		void setAlignment(int align);
		
		double getWidth();
		double getHeight();

		void draw();
};

#endif