#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <GL/freeglut.h>

class Drawable
{
	public:
		virtual void draw() = 0;
};

#endif