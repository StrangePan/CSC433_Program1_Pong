#ifndef _PONGGAME_H_
#define _PONGGAME_H_

#include <list>
#include "Board.h"
#include "Ball.h"
#include "Paddle.h"

class PongGame
{
	private:
		const int unit;

		bool game_active;
		bool game_paused;
		int p1_score;
		int p2_score;
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

		bool isPaused();
};

#endif
