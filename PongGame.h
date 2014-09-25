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

class PongGame : public Steppable
{
	private:
		bool game_active;
		bool game_paused;
		bool left_ai;
		bool right_ai;
		int left_score;
		int right_score;
		int width;
		int height;
		int x;
		int y;
		double ball_speed;
		int ball_timer;
		int hit_count;

		Board* board;
		Paddle* left_paddle;
		Paddle* right_paddle;
		Ball* ball;

		PaddleController* left_controller;
		PaddleController* right_controller;

		int left_paddle_size;
		int right_paddle_size;

		void updateDifficulty();
		void serve();
		void clear();
		void reset();

	public:
		PongGame();
		~PongGame();

		void step();
		void keyDownEvent(unsigned char key);
		void keyUpEvent(unsigned char key);
		void keySpecialDownEvent(int key);
		void keySpecialUpEvent(int key);
		void startGame(bool left_ai, bool right_ai);
		void quitGame();
		void pauseGame();
		void resumeGame();
		void scoreLeft();
		void scoreRight();
		void ballHit(bool right);
		void resetBall();
		void setBallSpeed( double speed );

		Board* getBoard();
		Paddle* getLeftPaddle();
		Paddle* getRightPaddle();
		Ball* getBall();

		bool isPaused();
};

#endif
