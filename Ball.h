#ifndef _BALL_H_
#define _BALL_H_

class Ball;

#include <cmath>
#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

/*! 
 * @brief The Ball Class Holds all the information to draw a ball for Pong
 *
 * @details The Ball holds information for its position, speed, and size
 *
 */
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
		 *  @brief draws the ball with the drawable class
		 */
		void draw();
};

#endif