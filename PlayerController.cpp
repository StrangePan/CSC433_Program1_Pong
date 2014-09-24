#include "PlayerController.h"

PlayerController::PlayerController(Paddle* paddle, bool arrows) :
		paddle(paddle), arrows(arrows)
{ }

void PlayerController::keyDown(int key)
{
	if (arrows)
	{
		switch (key)
		{
			case GLUT_KEY_UP:
				paddle -> up = true;
				break;
			case GLUT_KEY_DOWN:
				paddle -> down = true;
				break;
			case GLUT_KEY_LEFT:
				paddle -> left = true;
				break;
			case GLUT_KEY_RIGHT:
				paddle -> right = true;
				break;
			default:
				break;
		}
	}
	else
	{
		switch (toupper((char)key))
		{
			case 'W':
				paddle -> up = true;
				break;
			case 'S':
				paddle -> down = true;
				break;
			case 'A':
				paddle -> left = true;
				break;
			case 'D':
				paddle -> right = true;
				break;
			default:
				break;
		}
	}
}

void PlayerController::keyUp(int key)
{
	if (arrows)
	{
		switch (key)
		{
			case GLUT_KEY_UP:
				paddle -> up = false;
				break;
			case GLUT_KEY_DOWN:
				paddle -> down = false;
				break;
			case GLUT_KEY_LEFT:
				paddle -> left = false;
				break;
			case GLUT_KEY_RIGHT:
				paddle -> right = false;
				break;
			default:
				break;
		}
	}
	else
	{
		switch (toupper((char)key))
		{
			case 'W':
				paddle -> up = false;
				break;
			case 'S':
				paddle -> down = false;
				break;
			case 'A':
				paddle -> left = false;
				break;
			case 'D':
				paddle -> right = false;
				break;
			default:
				break;
		}
	}
}

void PlayerController::step()
{ }
