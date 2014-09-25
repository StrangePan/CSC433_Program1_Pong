#include "AIController.h"

AIController::AIController(Paddle* paddle, Ball* ball) :
		paddle(paddle), ball(ball)
{ }

void AIController::keyDown(unsigned char key)
{ }

void AIController::keyUp(unsigned char key)
{ }

void AIController::keySpecialDown(int key)
{ }
void AIController::keySpecialUp(int key)
{ }

void AIController::step()
{
	if (ball != NULL)
	{
		if (paddle->getY() != ball->center_y)
		{
			paddle->verticalMotion(ball->center_y - paddle->getY());
		}
	}
}