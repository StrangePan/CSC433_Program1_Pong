#ifndef _PADDLECONTROLLER_H_
#define _PADDLECONTROLLER_H_

class PaddleController;

#include "Steppable.h"

class PaddleController : public Steppable
{
	public:
		virtual void keyDown(unsigned char key) = 0;
		virtual void keyUp(unsigned char key) = 0;
		virtual void keySpecialDown(int key) = 0;
		virtual void keySpecialUp(int key) = 0;
		virtual void ballHit() = 0;
		virtual void step() = 0;
};

#endif