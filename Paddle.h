#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle;

#include "Drawable.h"
#include "Steppable.h"
#include "PongGame.h"

/*! 
 * @brief The Paddle class holds all the information for the paddle in Pong
 *
 * @details It keeps track of the location of the paddle, the size of the
 * paddle, and the max speed of the paddle.
 *
 */ 
class Paddle : public Drawable, public Steppable
{
	private:
		int height;
		int width;
		double center_x;
		double center_y;
		int maxx;
		int minx;
		int maxy;
		int miny;
		double vertical_paddle_speed;
		double horizontal_paddle_speed;
		PongGame* game;
	
	public:
		bool up;
		bool down;
		bool left;
		bool right;
		
		/*!
		 *  @brief The constructor, creates a paddle with position, size, and
		 *			max speed
		 */
		Paddle(PongGame* game, double x, double y, int width, int height,
			int maxx, int minx, int maxy, int miny);

		/*!
		 *  @brief handles the movement of the paddle
		 */
		void step();

		/*!
		 *  @brief handle vertical movement with a set speed
		 */
		void verticalMotion( double speed );

		/*!
		 *  @brief handles horizontal motion with a set speed
		 */
		void horizontalMotion( double speed );

		/*!
		 *  @brief sets the speed for the paddles
		 */
		void change_max_paddle_speed( double horizSpeed, double vertSpeed );

		/*!
		 *  @brief changes the height of the paddle
		 */
		void setHeight( int height );


		/*!
		 *  @brief returns the x coordinate of the paddle
		 */
		double getX();

		/*!
		 *  @brief returns the y cordinate of the paddle
		 */
		double getY();

		/*!
		 *  @brief returns the width of the paddles
		 */
		int getWidth();

		/*!
		 *  @brief The returns the height of the paddle
		 */
		int getHeight();



		/*!
		 *  @brief draws the paddle with the help of the drawable class
		 */
		void draw();
};

#endif