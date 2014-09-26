#include "PongGame.h"

PongGame::PongGame() :
		game_active(false), game_paused(false), board(NULL),
		left_paddle(NULL), right_paddle(NULL), ball(NULL),
		left_controller(NULL), right_controller(NULL),
		ball_timer(-1)
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
	if (ball_timer == 0 && ball != NULL && ball->x_velocity == 0 && ball->y_velocity == 0)
	{
		serve();
	}
	if (ball_timer > -1)
	{
		ball_timer--;
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
		left_controller->keySpecialDown(key);
	if (right_controller != NULL)
		right_controller->keySpecialDown(key);
}

void PongGame::keySpecialUpEvent(int key)
{
	if (left_controller != NULL)
		left_controller->keySpecialUp(key);
	if (right_controller != NULL)
		right_controller->keySpecialUp(key);
}

void PongGame::startGame(bool left_ai, bool right_ai)
{
	if (game_active) return;

	this -> left_ai = left_ai;
	this -> right_ai = right_ai;

	reset();

	game_active = true;
	game_paused = false;

	setBallSpeed( 5 );
	hit_count = 0;
	ball = new (nothrow) Ball(this, 0, 0, 20, 0, 0);
	resetBall();
	Pong::getInstance() -> drawObject( ball, 1 );

	if (left_ai)
	{
		left_controller = new AIController(left_paddle, ball);
		getLeftPaddle() -> change_max_paddle_speed( 2, 3 );
	}
	else
	{
		left_controller = new PlayerController(left_paddle, false);
		getLeftPaddle() -> change_max_paddle_speed( 2, 3 );
	}

	if (right_ai)
	{
		right_controller = new AIController(right_paddle, ball);
		getRightPaddle() -> change_max_paddle_speed( 2, 3 );
	}
	else
	{
		right_controller = new PlayerController(right_paddle, true);
		getRightPaddle() -> change_max_paddle_speed( 2, 3 );
	}

	updateDifficulty();
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
	left_score = 0;
	right_score = 0;
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

	board->setRightText(to_string(left_score));
	board->setLeftText(to_string(left_score));

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

void PongGame::scoreLeft()
{
	left_score++;
	if ( left_score == 10 )
	{
		leftWins();// ToDo End Game
	}
	board -> setLeftText( to_string( left_score ) );
	right_paddle_size = 8;
	left_paddle_size = 8;
	hit_count = 0;
	right_paddle->setHeight(right_paddle_size * Pong::unit);
	left_paddle->setHeight(left_paddle_size * Pong::unit);
	right_paddle->verticalMotion(0);
	left_paddle->verticalMotion(0);

	updateDifficulty();
	resetBall( );
}

void PongGame::leftWins()
{
	string text = "Left side Wins by " + to_string( left_score - right_score ) + " points";
	setEndText( text );

	Pong::getInstance() -> stopDrawingAll();
	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 ), (height ), 0);
    glutStrokeString(GLUT_STROKE_ROMAN, end_text);
    glPopMatrix();
}

void PongGame::scoreRight()
{
	right_score++;
	if ( right_score == 10 )
	{
		rightWins();// ToDo End Game
	}
	board -> setRightText( to_string( right_score ) );
	right_paddle_size = 8;
	left_paddle_size = 8;
	hit_count = 0;
	right_paddle->setHeight(right_paddle_size * Pong::unit);
	left_paddle->setHeight(left_paddle_size * Pong::unit);
	right_paddle->verticalMotion(0);
	left_paddle->verticalMotion(0);

	updateDifficulty();
	resetBall( );
}

void PongGame::rightWins( )
{
	string text = "Right side Wins by " + to_string( right_score - left_score ) + " points";
	setEndText( text );

	Pong::getInstance() -> stopDrawingAll();
	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2), (height / 2), 0);
    glutStrokeString(GLUT_STROKE_ROMAN, end_text);
    glPopMatrix();
}

void PongGame::setEndText( string text )
{
	int i = 0;
	end_text = new (nothrow) unsigned char[25];
	for( i = 0; i < 25; i++)
	{
		end_text[i] = '\0';
	}
	for (unsigned int i = 0; i < text.size(); i++)
	{
		end_text[i] = (unsigned char) text[i];
	};
	end_text[text.size()] = '\0';

}

void PongGame::ballHit(bool right)
{
	hit_count++;
	if (hit_count > 16 - (left_score + right_score) / 2)
	{
		if (right)
		{
			right_paddle_size--;
		}
		else
		{
			left_paddle_size--;
		}
	}
	if (right_paddle_size < 3)
	{
		right_paddle_size = 3;
	}
	if (left_paddle_size < 3)
	{
		left_paddle_size = 3;
	}
	right_paddle->setHeight(right_paddle_size * Pong::unit);
	left_paddle->setHeight(left_paddle_size * Pong::unit);

	if (right) {
		right_controller->ballHit();
	}
	else {
		left_controller->ballHit();
	}
}

void PongGame::updateDifficulty()
{
	if (left_ai)
	{
		left_paddle->change_max_paddle_speed(2, 3 + (right_score - left_score) * 0.125);
	}
	if (right_ai)
	{
		right_paddle->change_max_paddle_speed(2, 3 + (left_score - right_score) * 0.125);
	}
}

void PongGame::resetBall( )
{
	ball -> center_x = board -> getWidth() / 2;
	ball -> center_y = board -> getHeight() / 2;
	ball -> x_velocity = 0;
	ball -> y_velocity = 0;
	ball_timer = 60;
}

void PongGame::serve()
{
	if( (left_score + right_score) % 2 )
	{
		ball -> x_velocity = -ball_speed;
	}
	else
	{
		ball -> x_velocity = ball_speed;
	}
	ball -> y_velocity = (rand() % 11 - 5) / 2.0;
}

void PongGame::setBallSpeed( double speed )
{
	ball_speed = speed;
}
