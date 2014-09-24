#ifndef _PADDLECONTROLLER_H_
#define _PADDLECONTROLLER_H_

class PaddleController;

#include "Steppable.h"

class PaddleController : public Steppable
{
	public:
		virtual void keyDown(int key) = 0;
		virtual void keyUp(int key) = 0;
		virtual void step() = 0;
};

#endif