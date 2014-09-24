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
		if (paddle->getY() - ball->center_y >= 5)
		{
			paddle->down = true;
			paddle->up = false;
		}
		else if (paddle->getY() - ball->center_y <= -5)
		{
			paddle->down = false;
			paddle->up = true;
		}
		else
		{
			paddle->down = false;
			paddle->up = false;
		}
	}
}