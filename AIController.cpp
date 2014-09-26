#include "AIController.h"

AIController::AIController(Paddle* paddle, Ball* ball) :
paddle(paddle), ball(ball), offset(0)
{
	ballHit();
}

void AIController::keyDown(unsigned char key)
{ }

void AIController::keyUp(unsigned char key)
{ }

void AIController::keySpecialDown(int key)
{ }
void AIController::keySpecialUp(int key)
{ }

void AIController::ballHit()
{
	offset = (rand() % paddle->getHeight() - (paddle -> getHeight() / 2)) * 0.9;
}

void AIController::step()
{
	if (ball != NULL)
	{
		if (paddle->getY() != ball->center_y)
		{
			paddle->verticalMotion(ball->center_y - (paddle->getY() + offset));
		}
	}
}