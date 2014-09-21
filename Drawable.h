#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <gl/freeglut.h>

class Drawable
{
	public:
		virtual void draw() = 0;
};

#endif