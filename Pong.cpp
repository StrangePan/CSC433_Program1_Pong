/***************************************************************************//**
 * @file File containing the implementation of the Pong class.
 *
 * @brief Contains the implementation for the Pong class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Pong.h"

Pong* Pong::instance;
const int Pong::unit = 16;

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The constructor. Initializes variables and classes.
*******************************************************************************/
Pong::Pong() :
	view_width(32*unit), view_height(24*unit), window_width(view_width),
	window_height(view_height), window_name("Pong")
{
	if (instance == NULL)
		instance = this;

	// Instanciate game manager
	game = new (nothrow) PongGame;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: The destructor. Frees up dynamic memory.
*******************************************************************************/
Pong::~Pong()
{
	// Be sure to deallocate everything!
	delete game;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Function to get the current instance of the program.
 *
 * @returns Pointer to the current instance of the program.
*******************************************************************************/
Pong* Pong::getInstance()
{
	return instance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the current instance of the game manager.
 *
 * @returns Pointer to the current intance of the game manager.
*******************************************************************************/
PongGame* Pong::getGame()
{
	return game;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Begins running the program. Initializes OpenGL, registers
 *		events, instantiates objects, and runs the game. Beware when
 *		calling this function, as it enters the OpenGL main loop, only
 *		to return at end of program execution.
 *
 * @returns Status code of the program. 0 means no problems.
*******************************************************************************/
int Pong::run( int argc, char *argv[] )
{
	srand((unsigned int) time(NULL));

	// perform various OpenGL initializations
    glutInit( &argc, argv );

	// Put window in center of screen
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - view_width / 2;
		h = h / 2 - view_height / 2;
	}

	// Initialize glut with 32-bit graphics, double buffering, and anti-aliasing
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE );

	// Set up the program window
    glutInitWindowSize( view_width, view_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );         // window title

	// Always clear screen to black
	glClearColor( 0, 0, 0, 1.0 );

	glutIgnoreKeyRepeat(1);

    // Register callbacks
    glutDisplayFunc( *::display );
    glutReshapeFunc( *::reshape );
    glutKeyboardFunc( *::keyDown );
	glutKeyboardUpFunc( *::keyUp );
	glutSpecialFunc( *::keySpecialDown );
	glutSpecialUpFunc( *::keySpecialUp );
    glutMouseFunc( *::mouseclick );
	glutTimerFunc(0, *::step, 0);

    // Go into OpenGL/GLUT main loop
    glutMainLoop();

    return 0;

}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Registers a Drawable object to be drawn on demand.
 *
 * @param[in]	obj - Pointer to the object to draw
 * @param[in]	layer - OPTIONAL. The drawing layer of the object.
 *				Greater values will cause the object to be drawn above
 *				others. Negative values are allowed. Default is 0.
 *				Objects at the same layer are drawn in an undefined
 *				order.
*******************************************************************************/
void Pong::drawObject(Drawable* obj, int layer)
{
	if (!isDrawingObject(obj))
	{
		drawables[layer].push_back(obj);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Checks whether an object is currently being drawn.
 *
 * @param[in]	obj - Pointer to the object to search for.
 *
 * @returns True if the object is being drawn, false if not.
*******************************************************************************/
bool Pong::isDrawingObject(Drawable* obj)
{
	// Loop through every later and every object in that row until we find obj
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				return true;	// Found it!
			}
		}
	}
	return false;	// Didn't find it :(
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Determines the layer given the object is drawn at.
 *
 * @param[in]	-obj - Pointer to the object to search for.
 *
 * @returns The layer at which the object is being drawn. If object is
 *		not being drawn, will return 0.
*******************************************************************************/
int Pong::getDrawingLayer(Drawable* obj)
{
	// Loop through every later and every object in that row until we find obj
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				iterator -> first;
			}
		}
	}
	return 0;	// If object is not found, return default value of 0.
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Removes an object from the drawing list and no longer draws
 *		it. Must be done before the object becomes deallocated.
 *
 * @param[in]	obj - Pointer to the object to no longer draw.
*******************************************************************************/
void Pong::stopDrawingObject(Drawable* obj)
{
	// For every later, remove reference to object. Don't bother searching.
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		iterator->second.remove(obj);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Stops drawing all objects, clearing the drawing list.
*******************************************************************************/
void Pong::stopDrawingAll()
{
	drawables.clear();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the width of the view port in the virtual space.
 * 
 * @returns The width of the view port in pixels.
*******************************************************************************/
int Pong::getViewWidth()
{
	return view_width;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the height of the view port in the virtual space.
 *
 * @returns The height of the view port in pixels.
*******************************************************************************/
int Pong::getViewHeight()
{
	return view_height;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void Pong::display()
{
	//clear the display and set backround to black
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );
    
	// Draw all registered drawables
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			d->draw();
		}
	}

	// Flush graphical output
    glutSwapBuffers();
    glFlush();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void Pong::reshape(int w, int h)
{
	// store new window dimensions globally
    window_width = w;
    window_height = h;
	double ratio = (double) view_width / (double) view_height;
	double scale;

    // Orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );		// Use an orthographic projection
    glLoadIdentity();					// Initialize transformation matrix
	if (w > h * ratio)					// Adjust viewport based on ratio
	{
		scale = (double) h / (double) view_height;
		gluOrtho2D( 0 - ((w / scale) - view_width) / 2,
			view_width + ((w / scale) - view_width) / 2,
			0,
			view_height );
	}
	else
	{
		scale = (double) w / (double) view_width;
		gluOrtho2D( 0,
			view_width,
			0 - ((h / scale) - view_height) / 2,
			view_height + ((h / scale) - view_height) / 2 );
	}
    glViewport( 0, 0, w, h );			// Adjust viewport to new window

    // Switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Pong::keyDown(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 27:		// Escape
            exit( 0 );
            break;

		case 32:		// Space
			if ( game -> isRunning() )
			{
				if ( game -> isPaused() )
				{
					game -> resumeGame();
				}
				else
				{
					game -> pauseGame();
				}
			}
			else
			{
				game -> startGame(false, false);
			}
			break;

        default:		// Everything else, forward to game manager
			game->keyDownEvent(key);
            break;
    }
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key up callback. Executes whenever a typical key is
 *		released.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Pong::keyUp(unsigned char key, int x, int y)
{
	game->keyUpEvent(key);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key down callback. Executes whenever a "special"
 *		key such as an arrow key is pressed.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Pong::keySpecialDown(int key, int x, int y)
{
	game->keySpecialDownEvent(key);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key up callback. Executes whenever a "special" key
 *		such as an arrow key is released.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Pong::keySpecialUp(int key, int x, int y)
{
	game->keySpecialUpEvent(key);
}

/***************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 *		either clicked or released.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void Pong::mouseclick(int button, int state, int x, int y)
{
	// Correct for coordinate system
    y = view_height - y;

    switch ( button )
    {
        case GLUT_LEFT_BUTTON:		// left button
            break;

		case GLUT_RIGHT_BUTTON:		// right button
            break;
    }

	// Yeah... we don't do much in this function yet. We have plans though!
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Step callback. Called every frame of the game. Calls step
 *		function of other classes necessary for the game. Necessary
 *		for game elemnts that are not dependent on user interaction.
*******************************************************************************/
void Pong::step()
{
	game->step();
}

/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects. Simply
 *		forwards to Pong class' identical function.
*******************************************************************************/
void display()
{
	Pong::getInstance()->display();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *		Simply forwards to Pong class' identical function.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void reshape(int w, int h)
{
	Pong::getInstance()->reshape(w, h);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed. Simply forwards to Pong class' identical function.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keyDown(unsigned char key, int x, int y)
{
	Pong::getInstance()->keyDown(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key up callback. Executes whenever a typical key is
 *		released. Simply forwards to Pong class' identical function.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keyUp(unsigned char key, int x, int y)
{
	Pong::getInstance()->keyUp(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key down callback. Executes whenever a "special"
 *		key such as an arrow key is pressed. Simply forwards to Pong class'
 *		identical function.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keySpecialDown(int key, int x, int y)
{
	Pong::getInstance()->keySpecialDown(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key up callback. Executes whenever a "special" key
 * 		such as an arrow key is released. Simply forwards to Pong class'
 *		identical function.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keySpecialUp(int key, int x, int y)
{
	Pong::getInstance()->keySpecialUp(key, x, y);
}

/***************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 * 		either clicked or released. Simply forwards to Pong class'
 * 		identical function.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void mouseclick(int button, int state, int x, int y)
{
	Pong::getInstance()->mouseclick(button, state, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Step callback. Called every frame of the game. Calls step
 *		function of other classes necessary for the game. Necessary
 *		for game elemnts that are not dependent on user interaction.
 *		Simply to Pong class' step() function.
 *
 * @param[in]	i - Necessary for GLUT. Unused.
*******************************************************************************/
void step(int i)
{
	// FPS, or technically "milliseconds per frame"
	static unsigned int fps_delay = 1000 / 60;
	
	// Reset the timer
	glutTimerFunc(fps_delay, *::step, 0);
	
	// Call step function
	Pong::getInstance()->step();

	// Redraw the screen after frame's been processed.
	glutPostRedisplay();
}
