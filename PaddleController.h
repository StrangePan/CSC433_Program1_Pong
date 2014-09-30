/***************************************************************************//**
 * @file File containing the declaration for the PaddleController class.
 *
 * @brief Contains the declaration for the PaddleController class, an interface
 *		for classes designed to control paddles.
*******************************************************************************/
#ifndef _PADDLECONTROLLER_H_
#define _PADDLECONTROLLER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class PaddleController;

#include "Steppable.h"

/***************************************************************************//**
 * @brief The PaddleController class is really an interface for objects designed
 *		to take control of a Paddle object.
 *
 * @details This class declares a set of pure virtual functions that all objects
 *		designed to control a paddle must have in order to be valid.
*******************************************************************************/
class PaddleController : public Steppable
{
	public:

		/*!
		 * @brief Handles key press events.
		 */
		virtual void keyDown(unsigned char key) = 0;
		
		/*!
		 * @brief Handles key release events.
		 */
		virtual void keyUp(unsigned char key) = 0;
		
		/*!
		 * @brief Handles special key press events.
		 */
		virtual void keySpecialDown(int key) = 0;
		
		/*!
		 * @brief Handles special key release events.
		 */
		virtual void keySpecialUp(int key) = 0;
		
		/*!
		 * @brief Handles collision with ball events.
		 */
		virtual void ballHit() = 0;
		
		/*!
		 * @brief Executes every game step.
		 */
		virtual void step() = 0;
};

#endif