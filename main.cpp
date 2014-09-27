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
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      Build and run
 * 
 * @par Usage: 
   @verbatim  
   c:\> CSC433_Program1_Pong.exe 
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @todo add a menu
 * @todo add speed controls '+ -'
 * @todo change Pong bounch physics
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   09-12-2014	Made a plan on how to start
   09-15-2014	made most of the classes and defined possible functions
   09-17-2014	drew up the board and ball
   09-18-2014	Made the ball bounce randomly across the screen
   09-19-2014	Made the ball bounce off the paddles
   09-20-2014	Made the paddles move with jagged movements
   09-22-2014	added bounce physics and score removed left and right side
				wall bounce
   09-24-2014	change how the paddles get there input
   09-25-2014	Much improvement to the AI
   09-26-2014	making the program much closer to being able to be turned in
   @endverbatim
 *
 *****************************************************************************/

/*************************************************************************//**
 * @file 
 *
 * @brief Holds Initiallization for Primary Pong Class
 ****************************************************************************/
#include "Pong.h"

/**************************************************************************//** 
 * @author Dan Andrus
 * 
 * @par Description: 
 * This function priamarly passes the glut functionality to the Pong class
 * 
 * 
 * @param[in]      argc - Number of aurments from the commandline
 * @param[out]     argv - an array of commandline aurgments
 * 
 * @returns 0 program ran successful.
 * 
 * 
 *****************************************************************************/
int main( int argc, char *argv[] )
{
	Pong pong;	//initilizes head class
	return pong.run( argc, argv); //runs everything though class system
}
