#ifndef _AICONTROLLER_H_
#define _AICONTROLLER_H_

class AIController;

#include "PaddleController.h"
#include "Paddle.h"
#include "Ball.h"

class AIController : public PaddleController
{
	private:
		Paddle* paddle;
		Ball* ball;

	public:
		AIController(Paddle* paddle, Ball* ball);

		void keyDown(unsigned char key);
		void keyUp(unsigned char key);
		void keySpecialDown(int key);
		void keySpecialUp(int key);
		void step();
};

#endif