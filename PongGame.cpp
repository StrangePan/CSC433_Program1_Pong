/***************************************************************************//**
 * @file File containing the implementation of the PongGame class.
 *
 * @brief Contains the implementation for the PongGame class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "PongGame.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The constructor. Initializes variables and classes.
*******************************************************************************/
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

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The destructor. Frees up dynamic memory.
*******************************************************************************/
PongGame::~PongGame()
{
	clear();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Handles each step of the game. Does nothing if game is
 *		paused. Calls step() functions of objects that perform actions on each
 *		step, such as paddles, paddle controllers, and the ball.
*******************************************************************************/
void PongGame::step()
{
	// Don't do anything if the game is paused or if no game is running
	if (game_active && game_paused) return;

	// Forward paddle events to relevent objects
	if (left_paddle != NULL)
		left_paddle -> step();
	if (right_paddle != NULL)
		right_paddle -> step();
	if( ball != NULL )
		ball -> step();
	if (left_controller != NULL)
		left_controller->step();
	if (right_controller != NULL)
		right_controller->step();

	// Serve the ball if a serving timer is counting down
	if (ball_timer == 0
		&& ball != NULL
		&& ball->x_velocity == 0
		&& ball->y_velocity == 0)
	{
		serve();
	}

	// Decrement ball timer if applicable
	if (ball_timer > -1)
	{
		ball_timer--;
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Handles key press events.
 *
 * @param[in]	key - ASCII code of key pressed.
*******************************************************************************/
void PongGame::keyDownEvent(unsigned char key)
{
	// Forward event to paddle controllers (aka players)
	if (left_controller != NULL)
		left_controller->keyDown((char) key);
	if (right_controller != NULL)
		right_controller->keyDown((char) key);

	// Adjust ball speed
	if (ball != NULL && !game_paused)
	{
		if (key == '-' || key == '_')
		{
			ball->setSpeedModifier(ball->getSpeedModifier() - 0.25);
		}
		if (key == '=' || key == '+')
		{
			ball->setSpeedModifier(ball->getSpeedModifier() + 0.25);

			// Apply governor to ball speed. Too much, and we may lose it.
			if (ball->getSpeedModifier() > 2.0)
			{
				ball->setSpeedModifier(2.0);
			}
		}
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Handles key release events.
 *
 * @param[in]	key - ASCII code of key released.
*******************************************************************************/
void PongGame::keyUpEvent(unsigned char key)
{
	if (left_controller != NULL)
		left_controller->keyUp((char) key);
	if (right_controller != NULL)
		right_controller->keyUp((char) key);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Handles "special" key press events.
 *
 * @param[in]	key - GLUT enum of key pressed.
*******************************************************************************/
void PongGame::keySpecialDownEvent(int key)
{
	if (left_controller != NULL)
		left_controller->keySpecialDown(key);
	if (right_controller != NULL)
		right_controller->keySpecialDown(key);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Handles "special" key release events.
 *
 * @param[in]	key - GLUT enum of key released.
*******************************************************************************/
void PongGame::keySpecialUpEvent(int key)
{
	if (left_controller != NULL)
		left_controller->keySpecialUp(key);
	if (right_controller != NULL)
		right_controller->keySpecialUp(key);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Starts a new game of Pong if one isn't running already.
 *		Will automatically set up the board and any AI or player controllers.
 *		If a game is already running, will do nothing.
 *
 * @param[in]	left_ai - True to make the left paddle AI-controlled.
 * @param[in]	right_ai - True to make the right paddle AI-controlled.
*******************************************************************************/
void PongGame::startGame(bool left_ai, bool right_ai)
{
	// If a game is already running, just do nothing.
	if (game_active) return;

	this -> left_ai = left_ai;
	this -> right_ai = right_ai;

	// Get a blank slate. Clear everything and get new objects.
	reset();

	// Initialize game state
	game_active = true;
	game_paused = false;

	// Set up the ball
	ball_speed = 5;
	hit_count = 0;
	ball = new (nothrow) Ball(this, 0, 0, 20, 0, 0);
	resetBall();
	Pong::getInstance() -> drawObject( ball, 1 );

	// Set up paddle controllers
	if (left_ai)
		left_controller = new AIController(left_paddle, ball);
	else
		left_controller = new PlayerController(left_paddle, false);
	if (right_ai)
		right_controller = new AIController(right_paddle, ball);
	else
		right_controller = new PlayerController(right_paddle, true);
	
	// Don't display score if game is AI vs AI
	if (left_ai && right_ai)
	{
		board->setLeftText("");
		board->setRightText("");
	}

	getLeftPaddle() -> change_max_paddle_speed( 2, 3 );
	getRightPaddle() -> change_max_paddle_speed( 2, 3 );

	updateDifficulty();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Quits the current game.
*******************************************************************************/
void PongGame::quitGame()
{
	if (!game_active) return;
	game_active = false;
	Pong::getInstance() -> stopDrawingObject( ball );
	if (right_controller != NULL) delete right_controller;
	if (left_controller != NULL) delete left_controller;
	if (ball != NULL) delete ball;

	right_controller = NULL;
	left_controller = NULL;
	ball = NULL;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Pauses the current game.
*******************************************************************************/
void PongGame::pauseGame()
{
	game_paused = true;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Unpauses or resumes the current game.
*******************************************************************************/
void PongGame::resumeGame()
{
	game_paused = false;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Frees up memory and clears drawn objects from the screen.
*******************************************************************************/
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

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Destroys all game objects and rebuilds them.
*******************************************************************************/
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
	Pong::getInstance()->drawObject(board, 0);
	Pong::getInstance()->drawObject(left_paddle, 2);
	Pong::getInstance()->drawObject(right_paddle, 2);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to game board object.
 *
 * @returns Pointer to the board object.
*******************************************************************************/
Board* PongGame::getBoard()
{
	return board;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to the left paddle object.
 *
 * @returns Pointer to the left paddle.
*******************************************************************************/
Paddle* PongGame::getLeftPaddle()
{
	return left_paddle;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to the right paddle object.
 *
 * @returns Pointer to the right paddle.
*******************************************************************************/
Paddle* PongGame::getRightPaddle()
{
	return right_paddle;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to game ball object.
 *
 * @returns Pointer to the ball object.
*******************************************************************************/
Ball* PongGame::getBall()
{
	return ball;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Checks whether the game is currently paused.
 *
 * @returns True if the game is paused, false if not.
*******************************************************************************/
bool PongGame::isPaused()
{
	return game_paused;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Checks whether a game is currently running.
 *
 * @returns True if a game is running, false if not.
*******************************************************************************/
bool PongGame::isRunning()
{
	return game_active;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Scores one point for the left paddle.
*******************************************************************************/
void PongGame::scoreLeft()
{
	// If a player is playing, then keep track of score.
	if (!left_ai || !right_ai)
	{
		left_score++;
		board->setLeftText(to_string(left_score));
	}

	// Reset variables and paddle status
	hit_count = 0;
	right_paddle_size = 8;
	left_paddle_size = 8;
	right_paddle->setHeight(right_paddle_size * Pong::unit);
	left_paddle->setHeight(left_paddle_size * Pong::unit);

	// Since paddles could be outside border, move 0 px to fix position
	right_paddle->verticalMotion(0);
	left_paddle->verticalMotion(0);

	// Check if we have a winner
	if ( left_score == 10 )
	{
		leftWins();
		quitGame();
	}
	else
	{
		updateDifficulty();
		resetBall();
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Scores one point for the right paddle.
*******************************************************************************/
void PongGame::scoreRight()
{
	// If a player is playing, then keep track of score.
	if (!left_ai || !right_ai)
	{
		right_score++;
		board->setRightText(to_string(right_score));
	}

	// Reset variables and paddle status
	hit_count = 0;
	right_paddle_size = 8;
	left_paddle_size = 8;
	right_paddle->setHeight(right_paddle_size * Pong::unit);
	left_paddle->setHeight(left_paddle_size * Pong::unit);

	// Since paddles could be outside border, move 0 px to fix position
	right_paddle->verticalMotion(0);
	left_paddle->verticalMotion(0);

	// Check if we have a winner
	if ( right_score == 10 )
	{
		rightWins();
		quitGame();
	}
	else
	{
		updateDifficulty();
		resetBall();
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Makes the left player the winner. Displays a win message.
*******************************************************************************/
void PongGame::leftWins()
{
	board -> setCenterText("Left side wins!");
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Makes the right player the winner. Displays a win message.
*******************************************************************************/
void PongGame::rightWins()
{
	board -> setCenterText("Right side wins!");
}


/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Function handling the event that the ball hits a paddle.
 *		Adjust paddle sizes and makes call to update AI difficulty.
*******************************************************************************/
void PongGame::ballHit(bool right)
{
	// Increment hit count
	hit_count++;

	// Possibly shrink paddle sizes
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

	// Make sure paddles aren't impossibly small.
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

	// Let controllers know about the collision
	if (right) {
		right_controller->ballHit();
	}
	else {
		left_controller->ballHit();
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Updates AI difficulty based on score. Inscreases AI paddle
 *		max speed if AI is losing and slows it down if it is winning.
*******************************************************************************/
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

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Resets the game ball. Moves it to the center of the board
 *		 and sets the serve timer.
*******************************************************************************/
void PongGame::resetBall( )
{
	ball -> center_x = board -> getWidth() / 2;
	ball -> center_y = board -> getHeight() / 2;
	ball -> x_velocity = 0;
	ball -> y_velocity = 0;
	ball_timer = 60;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Serves the ball. Sets the ball's velocity to a constant
 *		horizontal velocity and a randomized vertical velocity.
*******************************************************************************/
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
