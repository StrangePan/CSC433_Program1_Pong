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
Pong::Pong() :
	view_width(32*unit), view_height(24*unit), window_width(view_width),
	window_height(view_height), window_name("Pong")
{
	if (instance == NULL)
		instance = this;

	// Instanciate game manager
	game = new (nothrow) PongGame;
}

Pong::~Pong()
{
	// Be sure to deallocate everything!
	delete game;
}

Pong* Pong::getInstance()
{
	return instance;
}

PongGame* Pong::getGame()
{
	return game;
}

void Pong::drawObject(Drawable* obj, int layer)
{
	if (!isDrawingObject(obj))
	{
		drawables[layer].push_back(obj);
	}
}

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

void Pong::stopDrawingAll()
{
	drawables.clear();
}

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

int Pong::getViewWidth()
{
	return view_width;
}

int Pong::getViewHeight()
{
	return view_height;
}

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
void Pong::keyUp(unsigned char key, int x, int y)
{
	game->keyUpEvent(key);
}
void Pong::keySpecialDown(int key, int x, int y)
{
	game->keySpecialDownEvent(key);
}
void Pong::keySpecialUp(int key, int x, int y)
{
	game->keySpecialUpEvent(key);
}

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

void Pong::step()
{
	game->step();
}

void display()
{
	Pong::getInstance()->display();
}

void reshape(int w, int h)
{
	Pong::getInstance()->reshape(w, h);
}

void keyDown(unsigned char key, int x, int y)
{
	Pong::getInstance()->keyDown(key, x, y);
}

void keyUp(unsigned char key, int x, int y)
{
	Pong::getInstance()->keyUp(key, x, y);
}

void keySpecialDown(int key, int x, int y)
{
	Pong::getInstance()->keySpecialDown(key, x, y);
}

void keySpecialUp(int key, int x, int y)
{
	Pong::getInstance()->keySpecialUp(key, x, y);
}

void mouseclick(int button, int state, int x, int y)
{
	Pong::getInstance()->mouseclick(button, state, x, y);
}

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
