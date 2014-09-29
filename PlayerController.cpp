/***************************************************************************//**
 * @file File containing the implementation of the PlayerController class.
 *
 * @brief Contains the implementation for the PlayerControler class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "PlayerController.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The constructor. Initializes variables and classes.
 * 
 * @param[in]	paddle - Pointer to paddle that this controller controls.
 * @param[in]	arrows - True/false value to indiciate whether this paddle
 *				should be listening for arrows (true) or WASD (false) controls.
*******************************************************************************/
PlayerController::PlayerController(Paddle* paddle, bool arrows) :
		paddle(paddle), arrows(arrows)
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Triggers when a keyboard key is pressed, such as the
 *		W, A, S, and D keys. Starts the paddle moving in the direction
 *		indiciated by the key no longer being pressed.
 *
 * @param[in]	key - ASCII code for the key being pressed
*******************************************************************************/
void PlayerController::keyDown(unsigned char key)
{
	if (!arrows)
	{
		switch (toupper(key))
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

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Triggers when a keyboard key is released, such as the
 *		W, A, S, and D keys. Stops the paddle from moving in the direction
 *		indiciated by the key no longer being pressed.
 *
 * @param[in]	key - ASCII code for the key no longer being pressed
*******************************************************************************/
void PlayerController::keyUp(unsigned char key)
{
	if (!arrows)
	{
		switch (toupper(key))
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

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Triggers when a "special" key is pressed, such as an
 *		arrow key. Starts the paddle moving in the direction indiciated by
 *		the key being pressed.
 *
 * @param[in]	key - GLUT enumerator for the key being pressed
*******************************************************************************/
void PlayerController::keySpecialDown(int key)
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
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Triggers when a "special" key is released, such as an
 *		arrow key. Stops the paddle from moving in the direction indiciated by
 *		the key no longer being pressed.
 *
 * @param[in]	key - GLUT enumerator for the key no longer being pressed
*******************************************************************************/
void PlayerController::keySpecialUp(int key)
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
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void PlayerController::ballHit()
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void PlayerController::step()
{ }
