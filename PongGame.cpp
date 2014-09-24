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
}

void PongGame::keyDownEvent(unsigned char key)
{ }

void PongGame::keyUpEvent(unsigned char key)
{ }

void PongGame::startGame()
{ 
	if (game_active) return;
	game_active = true;
	game_paused = false;
	ball = new (nothrow) Ball( this, width/2, height/2, 28, 2, 1 );
	Pong::getInstance() -> drawObject( ball, 1 );
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
	left_paddle = new (nothrow) Paddle(this, (int) (u * 2.5), height/2, u, left_paddle_size * u);
	right_paddle = new (nothrow) Paddle(this, width - (int) (u * 2.5), height/2, u, right_paddle_size * u);

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
