/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 1 - Pong
 * 
 * @section course_section Course Information 
 *
 * @author Dan Andrus, Johnny Ackerman
 * 
 * @date Sep 30, 2014
 * 
 * @par Professor: 
 *         Dr. Weiss
 * 
 * @par Course: 
 *         CSC-433 - M001-2014FA -  9:00-9:50 AM MWF
 * 
 * @par Location: 
 *         McLaury-311
 *
 * @section program_section Program Information 
 * 
 * @details This is an old style arcade game called Pong, in which you can 
 * verse a friend, or the AI. Players or AI face off by hitting a ball back
 * and forth accross a net with 2 paddles.
 * 
 * The WASD keys are used for the left player and the arrow keys are used
 * for the right player. The space bar pauses the current game or restarts
 * the game after a player scores ten points. The escape key ends the game.
 *
 * Glut and open GL are the libraries used for gui management.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      Build and run
 * 
 * @par Build:
   @verbatim
   > g++ -std=c++11 -lGL -lglut -lGLU -o pong AIController.cpp Ball.cpp\
       Board.cpp main.cpp Paddle.cpp PlayerController.cpp Pong.cpp PongGame.cpp
   @endverbatim
 * 
 * @par Make:
   @vertbatim
   > make pong
   @endverbatim
 * 
 * @par Usage: 
   @verbatim  
   > ./pong
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @todo add a menu
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   09-12-2014	Made a plan on how to start.
   09-15-2014	made most of the classes and defined possible functions.
   09-17-2014	Drew up the board and ball.
   09-18-2014	Made the ball bounce randomly across the screen.
   09-19-2014	Made the ball bounce off the paddles.
   09-20-2014	Made the paddles move with jagged movements.
   09-22-2014	Added bounce physics and score. Removed left and right side
				wall bounce.
   09-24-2014	Change how the paddles get there input.
   09-25-2014	Much improvement to the AI.
   09-26-2014	Clean ups and improvements.
   09-29-2014	Added compatability with Linux.
   09-30-2014	Added adjustable ball speeds & changed bouncing physics
   @endverbatim
 *
 *****************************************************************************/

#include "Pong.h"

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * This function priamarly passes control to the Pong class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
int main( int argc, char *argv[] )
{
	// Initialize program's core class
	Pong pong;

	// Run everything through the Pong class
	return pong.run( argc, argv);
}
