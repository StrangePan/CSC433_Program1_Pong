#ifndef _PONG_H_
#define _PONG_H_
using namespace std;

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
 *		the relationship between glut and the game for keyboard and mouse 
 *		management.
 *
 * @details This Class holds the gui window information.
 *
 */ 
class Pong
{
	private:
		static Pong* instance; /*!< holds private information of this class */
		int view_width; /*!<  */
		int view_height; /*!<  */
		int window_width; /*!< Width of gui window */
		int window_height; /*!< Height of gui window */
		string window_name; /*!< The Name of the Gui window */
		
		PongGame* game; /*!< Instance of another class, for communication */
		map<int, list<Drawable*>> drawables; /*!< list of drawable objects */

	public:
		static const int unit;

		/*!
		 *  @brief The constructor, initialize the game of Pong
		 */
		Pong ( );

		/*!
		 *  @brief The Destructor, deletes dynamic memory of game instance
		 */
		~Pong ( void );

		/*!
		 *  @brief Access function, allows other classes to see window
		 *		information
		 */
		static Pong* getInstance( );

		/*!
		 *  @brief Initializes the connection between glut callback
		 *		functions and creates the gui window
		 */
		int run ( int argc, char *argv[] );


		/*!
		 *  @brief Access function, allows other classes to see window
		 *		information
		 */
		PongGame* getGame();

		/*!
		 *  @brief Draws the various elements of the game (ball, paddle,
		 *		ect.)
		 */
		void drawObject(Drawable* obj, int layer = 0);

		/*!
		 *  @brief Sets the z demention of the object to put it above or
		 *		other objects
		 */
		void setDrawingLayer(Drawable* obj, int layer);

		/*!
		 *  @brief removes a given object from the screen
		 */
		void stopDrawingObject(Drawable* obj);

		/*!
		 *  @brief Destroys all drawn objects
		 */
		void stopDrawingAll();

		/*!
		 *  @brief determines if an object is of type drawable
		 */
		bool isDrawingObject(Drawable* obj);

		/*!
		 *  @brief determines the depth the object was drawn at
		 */
		int getDrawingLayer(Drawable* obj);

		/*!
		 *  @brief returns the width of the gui window
		 */
		int getViewWidth();
		/*!
		 *  @brief returns the height of the gui window
		 */
		int getViewHeight();
		
		/*!
		 *  @brief works with glut to draw the drawable objects
		 */
		void display();

		/*!
		 *  @brief Handles window resizing
		 */
		void reshape( int w, int h );

		/*!
		 *  @brief handles keyboard input as long as a key is pressed
		 */
		void keyDown(unsigned char key, int x, int y);

		/*!
		 *  @brief stops keyboard input as the key is released
		 */
		void keyUp(unsigned char key, int x, int y);

		/*!
		 *  @brief Handles when an "arrow key" is down
		 */
		void keySpecialDown(int key, int x, int y);

		/*!
		 *  @brief Handles the release of an "arrow key"
		 */
		void keySpecialUp(int key, int x, int y);

		/*!
		 *  @brief Handles MouseClicks and returns mouseclick posistion
		 */
		void mouseclick( int button, int state, int x, int y );

		/*!
		 *  @brief gets movement information from PongGame class and
		 *		gives it to the drawObject function
		 */
		void step();
};


/* these functions allow glut to communicate with the class functions */
void display();
void reshape( int w, int h );
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keySpecialDown(int key, int x, int y);
void keySpecialUp(int key, int x, int y);
void mouseclick( int button, int state, int x, int y );
void step(int i);

#endif
