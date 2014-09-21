#include "PongGame.h"

PongGame::PongGame() :
		game_active(false), game_paused(false), board(NULL),
		left_paddle(NULL), right_paddle(NULL), ball(NULL)
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
	{
		Pong::getInstance()->stopDrawingObject(board);
		delete board;
	}
	if (left_paddle != NULL)
	{
		Pong::getInstance()->stopDrawingObject(left_paddle);
		delete left_paddle;
	}
	if (right_paddle != NULL)
	{
		Pong::getInstance()->stopDrawingObject(right_paddle);
		delete right_paddle;
	}
	if (ball != NULL)
	{
		Pong::getInstance()->stopDrawingObject(ball);
		delete ball;
	}
}

void PongGame::reset()
{
	int u = Pong::unit;
	clear();

	// Reset game variables
	p1_score = 0;
	p2_score = 0;
	left_paddle_size = 8;
	right_paddle_size = 8;

	// Construct game elements
	board = new (nothrow) Board(0, 0, width, height, u);
	left_paddle = new (nothrow) Paddle((int) (u * 2.5), height/2, u, left_paddle_size * u);
	right_paddle = new (nothrow) Paddle(width - (int) (u * 2.5), height/2, u, right_paddle_size * u);

	board->setRightText("0");
	board->setLeftText("1");

	// Register game elements with drawing system
	Pong::getInstance()->drawObject(board);
	Pong::getInstance()->drawObject(left_paddle, 1);
	Pong::getInstance()->drawObject(right_paddle, 1);
}

bool PongGame::isPaused()
{
	return game_paused;
}
