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
	window_height(view_height), window_name("Pong"), menu(NULL), view_x(0),
	view_y(0)
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
	if (menu != NULL)
		delete menu;
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

	// Start the game
	game->startGame(true, true);
	displayMenu();

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
 * @author Johnny Ackerman
 * 
 * @par Description: Gets a pointer to game Menu object.
 *
 * @returns Pointer to the Menu object.
*******************************************************************************/
Menu* Pong::getMenu()
{
	return menu;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Displays the game menu
*******************************************************************************/
void Pong::displayMenu()
{
	if (menu != NULL) return;

	// Set up the variables
	MenuItem* item;
	double item_x = view_width / 2 - unit * 10;
	double item_y = view_height / 2 + unit * 1;
	double item_w = unit * 20;	// width
	double item_h = unit * 4;	// height
	double item_b = unit / 2;	// border
	double item_p = unit / 2;	// padding
	double item_m = unit / 2;	// margin
	
	// Build menu
	menu = new (nothrow) Menu(0, 0, 0, 0, Pong::unit / 2, "");
	menu -> setSize( unit * 22, unit * 18 );
	menu -> setPosition( view_width / 2 - unit * 11, view_height / 2 - unit * 9 );
	drawObject(menu, 3);
	
	// Set menu title
	if (game -> isDemo() || !game -> isRunning())
	{
		menu -> setTitle( "Main Menu" );
	}
	else
	{
		menu -> setTitle( "Pause" );
	}
	
	// Build each menu item
	// MenuItem(Menu* menu, double x, double y, double width, double height, string text, function<void ()> callback = [](){});
	
	// Continue/start game item(s)
	if (game -> isDemo() || !game -> isRunning())
	{
		// Single player game
		item = new (nothrow) MenuItem(menu, item_x, item_y, item_w, item_h, item_b, "New Solo Game");
		item -> setAction([](){
			Pong::getInstance() -> getGame() -> quitGame();
			Pong::getInstance() -> getGame() -> startGame(true, false);
			Pong::getInstance() -> closeMenu();
		});
		menu -> addItem(item);
		item_y -= item_h + item_m;
		
		// Multiplayer game
		item = new (nothrow) MenuItem(menu, item_x, item_y, item_w, item_h, item_b, "New Versus Game");
		item -> setAction([](){
			Pong::getInstance() -> getGame() -> quitGame();
			Pong::getInstance() -> getGame() -> startGame(false, false);
			Pong::getInstance() -> closeMenu();
		});
		menu -> addItem(item);
		item_y -= item_h + item_m;
	}
	else
	{
		// Continue
		item = new (nothrow) MenuItem(menu, item_x, item_y, item_w, item_h, item_b, "Continue");
		item -> setAction([](){
			Pong::getInstance() -> getGame() -> resumeGame();
			Pong::getInstance() -> closeMenu();
		});
		menu -> addItem(item);
		item_y -= item_h + item_m;

		// Quit Game
		item = new (nothrow) MenuItem(menu, item_x, item_y, item_w, item_h, item_b, "Quit Game");
		item -> setAction([](){
			Pong::getInstance() -> getGame() -> quitGame();
			Pong::getInstance() -> getGame() -> startGame(true, true);
			Pong::getInstance() -> closeMenu();
			Pong::getInstance() -> displayMenu();
		});
		menu -> addItem(item);
		item_y -= item_h + item_m;
	}
	
	// Quit Pong
	item = new (nothrow) MenuItem(menu, item_x, item_y, item_w, item_h, item_b, "Quit Pong");
	item -> setAction([](){
		exit(0);
	});
	menu -> addItem(item);
	item_y -= item_h + item_m;
	
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Closes any open menus
*******************************************************************************/
void Pong::closeMenu()
{
	if (game -> isRunning() && !game -> isDemo() && game -> isPaused())
	{
		game -> resumeGame();
	}
	if (menu != NULL)
	{
		stopDrawingObject(menu);
		delete menu;
		menu = NULL;
	}
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
		this -> scale = scale;
		gluOrtho2D( 0 - ((w / scale) - view_width) / 2,
			view_width + ((w / scale) - view_width) / 2,
			0,
			view_height );
		
		view_x = (w / scale - view_width) / 2;
		view_y = 0;
	}
	else
	{
		scale = (double) w / (double) view_width;
		this -> scale = scale;
		gluOrtho2D( 0,
			view_width,
			0 - ((h / scale) - view_height) / 2,
			view_height + ((h / scale) - view_height) / 2 );

		view_x = 0;
		view_y = (h / scale - view_height) / 2;
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
			game -> quitGame();
			closeMenu();
            exit( 0 );
            break;

		case 32:		// Space
			if ( game -> isRunning() && !game -> isDemo() )
			{
				if ( game -> isPaused() )
				{
					closeMenu();
				}
				else
				{
					game -> pauseGame();
					displayMenu();
				}
			}
			else
			{
				displayMenu();
				game -> startGame(true, true);
			}
			break;

        default:		// Everything else, forward to game manager
			game -> keyDownEvent(key);
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
    y = window_height - y;

	// Correct for scaling
	x /= scale;
	y /= scale;

	x -= view_x;
	y -= view_y;

    switch ( button )
    {
        case GLUT_LEFT_BUTTON:		// left button
			if (menu != NULL) menu -> click( button, state, x, y );
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
