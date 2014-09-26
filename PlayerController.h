#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

class PlayerController;

#include <gl/freeglut.h>
#include "PaddleController.h"
#include "Paddle.h"

class PlayerController : public PaddleController
{
	private:
		bool arrows;
		Paddle* paddle;

	public:
		PlayerController(Paddle* paddle, bool arrows);

		void keyDown(unsigned char key);
		void keyUp(unsigned char key);
		void keySpecialDown(int key);
		void keySpecialUp(int key);
		void ballHit();
		void step();
};

#endif