/***************************************************************************//**
 * @file File containing the declaration for the PlayerController class.
 *
 * @brief Contains the declaration for the PlayerController class, a class
 *		designed to allow a player to control a Pong paddle.
*******************************************************************************/
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class PlayerController;

#include <GL/freeglut.h>
#include "PaddleController.h"
#include "Paddle.h"

/***************************************************************************//**
 * @brief The PlayerController class is designed to allow a user to control
 *		a Pong paddle through 
 *
 * @details This class declares a set of pure virtual functions that all objects
 *		designed to control a paddle must have in order to be valid.
*******************************************************************************/
class PlayerController : public PaddleController
{
	private:
		bool arrows;	/*<! Flag to check for arrows or letters */
		Paddle* paddle;	/*<! Pointer to paddle we're controlling */

	public:
		/*!
		 * @brief The constructor. Initializes variables.
		 */
		PlayerController(Paddle* paddle, bool arrows);
		
		/*!
		 * @brief Handles WASD keys being pressed.
		 */
		void keyDown(unsigned char key);
		
		/*!
		 * @brief Handles WASD keys being released.
		 */
		void keyUp(unsigned char key);
		
		/*!
		 * @brief Handles arrow keys being pressed.
		 */
		void keySpecialDown(int key);
		
		/*!
		 * @brief Handles arrow keys being released.
		 */
		void keySpecialUp(int key);
		
		/*!
		 * @brief Does nothing; fulfills superclass requirements.
		 */
		void ballHit();
		
		/*!
		 * @brief Does nothing; fulfills superclass requirements.
		 */
		void step();
};

#endif