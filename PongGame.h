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

using namespace std;

class PongGame : public Steppable
{
	private:
		bool game_active;
		bool game_paused;
		int left_score;
		int right_score;
		int width;
		int height;
		int x;
		int y;

		Board* board;
		Paddle* left_paddle;
		Paddle* right_paddle;
		Ball* ball;

		int left_paddle_size;
		int right_paddle_size;

		void clear();
		void reset();

	public:
		PongGame();
		~PongGame();

		void step();
		void keyDownEvent(unsigned char key);
		void keyUpEvent(unsigned char key);
		void startGame();
		void quitGame();
		void pauseGame();
		void resumeGame();
		void scoreLeft();
		void scoreRight();
		int getScore();
		void resetBall();

		Board* getBoard();
		Paddle* getLeftPaddle();
		Paddle* getRightPaddle();
		Ball* getBall();

		bool isPaused();
};

#endif
