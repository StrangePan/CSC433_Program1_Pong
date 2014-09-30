/***************************************************************************//**
 * @file File containing the declaration for the Ball class.
 *
 * @brief Contains the declaration for the Ball class.
*******************************************************************************/
#ifndef _BALL_H_
#define _BALL_H_

class Ball;

#include <cmath>
#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

/***************************************************************************//**
 * @brief The Ball Class Holds all the information to draw a ball for Pong
 *
 * @details The Ball holds information for its position, speed, and size
*******************************************************************************/
class Ball : public Drawable, public Steppable
{
	public:
		double center_x;	/*!< x coordinate for the center of the ball on
									in the coordinate plane */
		double center_y;	/*!< y coordinate for the center of the ball on
									in the coordinate plane */
		int width;			/*!< radius of the ball */
		double x_velocity;	/*!< x speed of the ball */
		double y_velocity;	/*!< y speed of the ball */
		double s_velocity;	/*!< Velocity scalar for varying speeds */
		PongGame* game;		/*!< instance of the pongGame class that is in
									charge of the ball class */

		/*!
		 *  @brief The constructor, creates the ball with location, size, and
		 *			speed
		 */
		Ball(PongGame* game, double x, double y, int width, double x_velocity, double y_velocity);

		/*!
		 *  @brief Handles the ball movement
		 */
		void step();

		/*!
		 * @brief Sets a modifier on the ball's speed. 1 means normal, less
		 *		than 1 will slow the ball down, greater than 1 will speed it up.
		 */
		void setSpeedModifier(double s_velocity);

		/*!
		 * @brief Gets the ball's current speed modifier.
		 */
		double getSpeedModifier();

		/*!
		 *  @brief Draws the ball on the screen
		 */
		void draw();
};

#endif