#include "PongGame.h"

PongGame::PongGame() :
		game_active(false), game_paused(false), board(NULL),
		left_paddle(NULL), right_paddle(NULL), ball(NULL),
		left_controller(NULL), right_controller(NULL)
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
{
	if (game_active && game_paused) return;

	if (left_paddle != NULL)
	{
		left_paddle -> step();
	}
	if (right_paddle != NULL)
	{
		right_paddle -> step();
	}
	if( ball != NULL )
	{
		ball -> step();
	}
	if (left_controller != NULL)
	{
		left_controller->step();
	}
	if (right_controller != NULL)
	{
		right_controller->step();
	}
}

void PongGame::keyDownEvent(unsigned char key)
{
	if (left_controller != NULL)
		left_controller->keyDown((char) key);
	if (right_controller != NULL)
		right_controller->keyDown((char) key);
}

void PongGame::keyUpEvent(unsigned char key)
{
	if (left_controller != NULL)
		left_controller->keyUp((char) key);
	if (right_controller != NULL)
		right_controller->keyUp((char) key);
}

void PongGame::keySpecialDownEvent(int key)
{
	if (left_controller != NULL)
		left_controller->keyDown(key);
	if (right_controller != NULL)
		right_controller->keyDown(key);
}

void PongGame::keySpecialUpEvent(int key)
{
	if (left_controller != NULL)
		left_controller->keyUp(key);
	if (right_controller != NULL)
		right_controller->keyUp(key);
}

void PongGame::startGame(bool left_ai, bool right_ai)
{
	if (game_active) return;
	reset();

	game_active = true;
	game_paused = false;

	ball = new (nothrow) Ball( this, width/2, height/2, 28, 2, 1 );
	Pong::getInstance() -> drawObject( ball, 1 );

	if (left_ai)
	{
		left_controller = new AIController(left_paddle, ball);
	}
	else
	{
		left_controller = new PlayerController(left_paddle, false);
	}

	if (right_ai)
	{
		right_controller = new AIController(right_paddle, ball);
	}
	else
	{
		right_controller = new PlayerController(right_paddle, true);
	}
}

void PongGame::quitGame()
{
	if (!game_active) return;
	game_active = false;
	if (ball != NULL) delete ball;
}

void PongGame::pauseGame()
{
	game_paused = true;
}

void PongGame::resumeGame()
{
	game_paused = false;
}

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
	if (left_controller != NULL)
	{
		delete left_controller;
	}
	if (right_controller != NULL)
	{
		delete right_controller;
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
	left_paddle = new (nothrow) Paddle(this,
		(int) (u * 2.5),
		height/2,
		u,
		left_paddle_size * u,
		board->getX() + board->getWidth() / 4,
		board->getX(),
		board->getY() + board->getHeight(),
		board->getY());
	right_paddle = new (nothrow) Paddle(this,
		width - (int) (u * 2.5),
		height/2,
		u,
		right_paddle_size * u,
		board->getX() + board->getWidth(),
		board->getX() + board->getWidth() / 4 * 3,
		board->getY() + board->getHeight(),
		board->getY());

	board->setRightText(to_string(p1_score));
	board->setLeftText(to_string(p2_score));

	// Register game elements with drawing system
	Pong::getInstance()->drawObject(board);
	Pong::getInstance()->drawObject(left_paddle, 1);
	Pong::getInstance()->drawObject(right_paddle, 1);
}

Board* PongGame::getBoard()
{
	return board;
}

Paddle* PongGame::getLeftPaddle()
{
	return left_paddle;
}

Paddle* PongGame::getRightPaddle()
{
	return right_paddle;
}

Ball* PongGame::getBall()
{
	return ball;
}

bool PongGame::isPaused()
{
	return game_paused;
}
