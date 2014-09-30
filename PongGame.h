#ifndef _PONGGAME_H_
#define _PONGGAME_H_

class PongGame;

#include <list>
#include <string>
#include "Pong.h"
#include "Board.h"
#include "Paddle.h"
#include "Ball.h"
#include "Steppable.h"

#include "AIController.h"
#include "PlayerController.h"
#include "PaddleController.h"

using namespace std;

/*! 
 * @brief The PongGame Class runs the entire game of pong, It is in charge
 *		of all parts of the game logic.
 *
 * @details PongGame determines whether the game is pause, it restarts the
 *		game if space is pressed on the end screen. The only thing it 
 *		doesn't do is handle the drawing of the parts. That is handle up
 *		from the class that needs something drawn to the Pong class, and
 *		then to the drawable class.
 *
 */ 
class PongGame : public Steppable
{
	private:
		bool game_active;	/*!< determins if game is playing */
		bool game_paused;	/*!< determins if game is paused */
		bool left_ai;	/*!< determines if left_ai is on */
		bool right_ai;	/*!< determines if right_ai is on */
		int left_score;	/*!< Points made for left side */
		int right_score;	/*!< The score of the right side */
		int width;	/*!< View width from Pong.h */
		int height;	/*!< View_hieght from Pong.h */
		double ball_speed;	/*!< The x velocity of the ball */
		int ball_timer;	/*!< timer before ball is served */
		int hit_count;	/*!< amount of times a paddle has been hit by the ball */

		Board* board;	/*!< instance of the board class */
		Paddle* left_paddle;	/*!< instance of paddle on the left side */
		Paddle* right_paddle;	/*!< right instance of paddle */
		Ball* ball;	/*!< Stores the comment */

		PaddleController* left_controller;	/*!< instance of class that controls the
												left paddle*/
		PaddleController* right_controller;	/*!< instance of class that controls the
												right paddle*/

		int left_paddle_size;	/*!< height of the left paddle */
		int right_paddle_size;	/*!< height of the right paddle */

		/*!
		 *  @brief Changes ai difficulty
		 */
		void updateDifficulty();
		
		/*!
		 *  @brief alternates serve
		 */
		void serve();
		
		/*!
		 *  @brief Deletes instance of classes that PongGame is in charge of
		 */
		void clear();

		/*!
		 *  @brief resets all data
		 */
		void reset();

	public:

		/*!
		 *  @brief The constructor, initialize PongGame and gets a width and 
		 *		height from the Pong class
		 */
		PongGame();

		/*!
		 *  @brief The destructor, destroys subclasses and itself
		 */
		~PongGame();

		/*!
		 *  @brief Moves various parts of the game
		 */
		void step();

		/*!
		 *  @brief registers that a key was pressed
		 */
		void keyDownEvent(unsigned char key);

		/*!
		 *  @brief registers that a key was released
		 */
		void keyUpEvent(unsigned char key);

		/*!
		 *  @brief registers that an "arrow" key was pressed
		 */
		void keySpecialDownEvent(int key);

		/*!
		 *  @brief registers that an "arrow" key was released
		 */
		void keySpecialUpEvent(int key);

		/*!
		 *  @brief Starts the game with 0, 1, or 2 players
		 */
		void startGame(bool left_ai, bool right_ai);

		/*!
		 *  @brief Ends the game but leaves the board
		 */
		void quitGame();

		/*!
		 *  @brief Pauses the game and all parts of it from moving
		 */
		void pauseGame();

		/*!
		 *  @brief lets everything move again
		 */
		void resumeGame();

		/*!
		 *  @brief Increments the left score and ends game at 10
		 */
		void scoreLeft();

		/*!
		 *  @brief Increaments the right score and ends game at 10
		 */
		void scoreRight();

		/*!
		 *  @brief counts the amount of times the ball has been hit and
		 *		shrinks the paddles accordingly
		 */
		void ballHit(bool right);

		/*!
		 *  @brief resets the ball after a score
		 */
		void resetBall();

		/*!
		 *  @brief Sets the speed of the ball
		 */
		void setBallSpeed( double speed );


		/*!
		 *  @brief quits the game and outputs "Left Side Wins"
		 */
		void leftWins();

		/*!
		 *  @brief quits the game and outputs "Right Side Wins"
		 */
		void rightWins();

		/*!
		 *  @brief acceses the board class
		 */
		Board* getBoard();

		/*!
		 *  @brief accesses the left paddle entity
		 */
		Paddle* getLeftPaddle();

		/*!
		 *  @brief accesses the right paddle entity
		 */
		Paddle* getRightPaddle();

		/*!
		 *  @brief accesses the ball entity
		 */
		Ball* getBall();


		/*!
		 *  @brief determines if the game is paused
		 */
		bool isPaused();

		/*!
		 *  @brief determines if the game is running
		 */
		bool isRunning();
};

#endif
