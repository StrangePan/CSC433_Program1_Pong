/***************************************************************************//**
 * @file File containing the implementation of the AIController class.
 *
 * @brief Contains the implementation for the AIController class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "AIController.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The constructor. Initializes variables and classes.
 *		Triggers the ballHit() function to randomize offset.
 * 
 * @param[in]	paddle - Pointer to paddle that this controller controls.
 * @param[in]	ball - Pointer to the ball object to track.
*******************************************************************************/
AIController::AIController(Paddle* paddle, Ball* ball) :
paddle(paddle), ball(ball), offset(0)
{
	ballHit();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void AIController::keyDown(unsigned char key)
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void AIController::keyUp(unsigned char key)
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void AIController::keySpecialDown(int key)
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Does nothing. Fulfills superclass requirements.
*******************************************************************************/
void AIController::keySpecialUp(int key)
{ }

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Triggers when ball bounces off paddle that this controller
 *		controls. Randomizes the AI's offset.
*******************************************************************************/
void AIController::ballHit()
{
	offset = (rand() % 3 * Pong::unit - (3 * Pong::unit / 2)) * 0.8;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Moves the paddle vertically if it is not aligned with the
 *		ball.
*******************************************************************************/
void AIController::step()
{
	if (ball != NULL)		// This is entirely a possibility
	{
		if (paddle->getY() + offset != ball->center_y)
		{
			paddle->verticalMotion(ball->center_y - (paddle->getY() + offset));
		}
	}
}