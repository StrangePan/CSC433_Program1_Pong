#include "Pong.h"
#include "PongGame.h"

PongGame::PongGame() :
		unit(16), game_active(false), game_paused(false)
{
	Pong* pong = Pong::getInstance();
	width = pong->getViewWidth();
	height = pong->getViewHeight();
	
	reset();
}

PongGame::~PongGame()
{
	clear();
}


void PongGame::step()
{ }

void PongGame::keyDownEvent(unsigned char key)
{ }

void PongGame::keyUpEvent(unsigned char key)
{ }

void PongGame::startGame()
{ }

void PongGame::quitGame()
{ }

void PongGame::pauseGame()
{ }

void PongGame::resumeGame()
{ }

void PongGame::clear()
{
	if (board != NULL)
		delete board;
	if (left_paddle != NULL)
		delete left_paddle;
	if (right_paddle != NULL)
		delete right_paddle;
	if (ball != NULL)
		delete ball;
}

void PongGame::reset()
{
	clear();
	p1_score = 0;
	p2_score = 0;
	left_paddle_size = 8;
	right_paddle_size = 8;
	board = new (nothrow) Board(0, 0, width, height);
	left_paddle = new (nothrow) Paddle(unit + unit/2, height/2, unit, left_paddle_size * unit);
	right_paddle = new (nothrow) Paddle(width - unit - unit/2, height/2, unit, right_paddle_size * unit);
}

bool PongGame::isPaused()
{
	return game_paused;
}
