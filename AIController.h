/***************************************************************************//**
 * @file File containing the declaration for the AIController class.
 *
 * @brief Contains the declaration for the AIController class.
*******************************************************************************/
#ifndef _AICONTROLLER_H_
#define _AICONTROLLER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class AIController;

#include "PaddleController.h"
#include "Paddle.h"
#include "Ball.h"

/***************************************************************************//**
 * @brief The AIController class moves a pong paddle to intersect a ball with
 * 
 * @details This class acts as AI for single player games. It gains control
 *		of a pong paddle and attempts to line up with it along the X axis.
 *		Chooses a random offset every hit to switch up the game.
*******************************************************************************/
class AIController : public PaddleController
{
	private:
		Paddle* paddle;		/*!< Pointer to paddle under AI control */
		Ball* ball;			/*!< Pointer to ball to watch */
		double offset;		/*!< Random offset to align the ball with */

	public:
		/*!
		 * @brief The constructor. Initializes variables.
		 */
		AIController(Paddle* paddle, Ball* ball);
		
		/*!
		 * @brief Does nothing; fulfulls superclass requirements
		 */
		void keyDown(unsigned char key);
		
		/*!
		 * @brief Does nothing; fulfulls superclass requirements
		 */
		void keyUp(unsigned char key);
		
		/*!
		 * @brief Does nothing; fulfulls superclass requirements
		 */
		void keySpecialDown(int key);
		
		/*!
		 * @brief Does nothing; fulfulls superclass requirements
		 */
		void keySpecialUp(int key);
		
		/*!
		 * @brief Randomizes offset to align the ball with
		 */
		void ballHit();
		
		/*!
		 * @brief Moves the paddle a little closer to be aligned with the ball.
		 */
		void step();
};

#endif
