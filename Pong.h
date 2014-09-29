/***************************************************************************//**
 * @file File containing the declaration for the Pong class.
 *
 * @brief Contains the declaration for the Pong class, the core class of the
 * entire program.
*******************************************************************************/
#ifndef _PONG_H_
#define _PONG_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
using namespace std;

class Pong;

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <GL/freeglut.h>
#include <time.h>
#include "PongGame.h"
#include "Drawable.h"

/*! 
 * @brief The Pong Class is in charge of window management, drawing all the
 *		parts of the game, and running the other classes. It also handles
 *		the interfacing between glut and the game for keyboard and mouse 
 *		management.
 *
 * @details This Class essentially provides a base for the rest of the program.
 *		It handles drawing functions, forwards OpenGL events, generates a
 *		framerate, and standardizes various aspects of the game.
 */ 
class Pong
{
	private:
		static Pong* instance;	/*!< reference to main instance of this class */
		int view_width;			/*!< The width of the drawable region */
		int view_height;		/*!< The height of the drawable region */
		int window_width;		/*!< Width of gui window */
		int window_height;		/*!< Height of gui window */
		string window_name;		/*!< The Name of the Gui window */
		
		PongGame* game;			/*!< Pointer to instance of the game manager */
		map<int, list<Drawable*>> drawables;	/*!< list of objects to draw*/

	public:
		static const int unit;	/*!< Unit of measurement used in calculations */

		/*!
		 * @brief The constructor. Initializes variables and classes.
		 */
		Pong ( );

		/*!
		 * @brief The destructor. Frees up dynamic memory.
		 */
		~Pong ( void );

		/*!
		 * @brief Function to get the current instance of the program.
		 *
		 * @returns Pointer to the current instance of the program.
		 */
		static Pong* getInstance( );

		/*!
		 * @brief Begins running the program. Initializes OpenGL, registers
		 *		events, instantiates objects, and runs the game. Beware when
		 *		calling this function, as it enters the OpenGL main loop, only
		 *		to return at end of program execution.
		 *
		 * @returns Status code of the program. 0 means no problems.
		 */
		int run ( int argc, char *argv[] );


		/*!
		 * @brief Gets the current instance of the game manager.
		 *
		 * @returns Pointer to the current intance of the game manager.
		 */
		PongGame* getGame();

		/*!
		 * @brief Registers a Drawable object to be drawn on demand.
		 *
		 * @param[in]	obj - Pointer to the object to draw
		 * @param[in]	layer - OPTIONAL. The drawing layer of the object.
		 *				Greater values will cause the object to be drawn above
		 *				others. Negative values are allowed. Default is 0.
		 *				Objects at the same layer are drawn in an undefined
		 *				order.
		 */
		void drawObject(Drawable* obj, int layer = 0);

		/*!
		 * @brief Sets the drawing layer of an already registered object.
		 *
		 * @param[in]	obj - Pointer to the object in question.
		 * @param[in]	layer - The new layer of the object.
		 */
		void setDrawingLayer(Drawable* obj, int layer);

		/*!
		 * @brief Removes an object from the drawing list and no longer draws
		 *		it. Must be done before the object becomes deallocated.
		 *
		 * @param[in]	obj - Pointer to the object to no longer draw.
		 */
		void stopDrawingObject(Drawable* obj);

		/*!
		 * @brief Stops drawing all objects, clearing the drawing list.
		 */
		void stopDrawingAll();

		/*!
		 * @brief Checks whether an object is currently being drawn.
		 *
		 * @param[in]	obj - Pointer to the object to search for.
		 *
		 * @returns True if the object is being drawn, false if not.
		 */
		bool isDrawingObject(Drawable* obj);

		/*!
		 * @brief Determines the layer given the object is drawn at.
		 *
		 * @param[in]	-obj - Pointer to the object to search for.
		 *
		 * @returns The layer at which the object is being drawn. If object is
		 *		not being drawn, will return 0.
		 */
		int getDrawingLayer(Drawable* obj);

		/*!
		 * @brief Gets the width of the view port in the virtual space.
		 * 
		 * @returns The width of the view port in pixels.
		 */
		int getViewWidth();

		/*!
		 * @brief Gets the height of the view port in the virtual space.
		 *
		 * @returns The height of the view port in pixels.
		 */
		int getViewHeight();
		
		/*!
		 * @brief Drawing callback. Executes every glut display callaback. Also
		 *		calls the draw function of all registerd Drawable objects.
		 */
		void display();

		/*!
		 * @brief Resize callback. Executes whenever the window is resized.
		 *
		 * @param[in]	w - The window's new width in pixels.
		 * @param[in]	h - The window's new height in pixels.
		 */
		void reshape( int w, int h );

		/*!
		 * @brief Key down callback. Executes whenever a typical key is pressed.
		 *
		 * @param[in]	key - ASCII-encoded char of the key that was pressed.
		 * @param[in]	x - The x coordinate of the mouse at the time the key
		 *				was pressed. Measured in integers.
		 * @param[in]	y - The y coordinate of the mouse at the time the key
		 *				was pressed.
		 */
		void keyDown(unsigned char key, int x, int y);

		/*!
		 * @brief Key up callback. Executes whenever a typical key is released.
		 * 
		 * @param[in]	key - ASCII-encoded char of the key that was pressed.
		 * @param[in]	x - The x coordinate of the mouse at the time the key
		 *				was pressed. Measured in integers.
		 * @param[in]	y - The y coordinate of the mouse at the time the key
		 *				was pressed.
		 */
		void keyUp(unsigned char key, int x, int y);

		/*!
		 * @brief Special key down callback. Executes whenever a "special" key
		 *		such as an arrow key is pressed.
		 *  
		 * @param[in]	key - Special GLUT enumerator of the key.
		 * @param[in]	x - The x coordinate of the mouse at the time the key
		 *				was pressed. Measured in integers.
		 * @param[in]	y - The y coordinate of the mouse at the time the key
		 *				was pressed.
		 */
		void keySpecialDown(int key, int x, int y);

		/*!
		 * @brief Special key up callback. Executes whenever a "special" key
		 *		such as an arrow key is released.
		 *  
		 * @param[in]	key - Special GLUT enumerator of the key.
		 * @param[in]	x - The x coordinate of the mouse at the time the key
		 *				was pressed. Measured in integers.
		 * @param[in]	y - The y coordinate of the mouse at the time the key
		 *				was pressed.
		 */
		void keySpecialUp(int key, int x, int y);

		/*!
		 * @brief Mouse click callback. Executes whenever a mouse button is
		 *		either clicked or released.
		 *  
		 * @param[in]	button - The button whose state was changed.
		 * @param[in]	state - The new state of the button.
		 * @param[in]	x - The x coordinate of the mouse at the time the button
		 *				was pressed. Measured in integers.
		 * @param[in]	y - The y coordinate of the mouse at the time the button
		 *				was pressed.
		 */
		void mouseclick( int button, int state, int x, int y );

		/*!
		 * @brief Step callback. Called every frame of the game. Calls step
		 *		function of other classes necessary for the game. Necessary
		 *		for game elemnts that are not dependent on user interaction.
		 */
		void step();
};

/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/*!
 * @brief Drawing callback. Executes every glut display callaback. Also
 *		calls the draw function of all registerd Drawable objects. simply
 *		forwards to Pong class' identical function.
 */
void display();

/*!
 * @brief Resize callback. Executes whenever the window is resized.
 *		Simply forwards to Pong class' identical function.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
 */
void reshape( int w, int h );

/*!
 * @brief Key down callback. Executes whenever a typical key is pressed.
 *		Simply forwards to Pong class' identical function.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
 */
void keyDown(unsigned char key, int x, int y);

/*!
 * @brief Key up callback. Executes whenever a typical key is released.
 *		Simply forwards to Pong class' identical function.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
 */
void keyUp(unsigned char key, int x, int y);

/*!
 * @brief Special key down callback. Executes whenever a "special" key
 * 		such as an arrow key is pressed. Simply forwards to Pong class'
 *		identical function.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
 */
void keySpecialDown(int key, int x, int y);

/*!
 * @brief Special key up callback. Executes whenever a "special" key
 * 		such as an arrow key is released. Simply forwards to Pong class'
 *		identical function.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
 */
void keySpecialUp(int key, int x, int y);

/*!
 * @brief Mouse click callback. Executes whenever a mouse button is
 * 		either clicked or released. Simply forwards to Pong class'
 * 		identical function.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
 */
void mouseclick( int button, int state, int x, int y );

/*!
 * @brief Step callback. Called every frame of the game. Calls step
 *		function of other classes necessary for the game. Necessary
 *		for game elemnts that are not dependent on user interaction.
 *		Simply to Pong class' step() function.
 *
 * @param[in]	i - Necessary for GLUT. Unused.
 */
void step(int i);

#endif
