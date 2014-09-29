#include "Pong.h"

Pong* Pong::instance;
const int Pong::unit = 16;

Pong::Pong() :
	view_width(32*unit), view_height(24*unit), window_width(view_width),
	window_height(view_height), window_name("Pong")
{
	if (instance == NULL)
		instance = this;
	game = new (nothrow) PongGame;
	game -> startGame(true, true);
}

Pong::~Pong()
{
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
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin(); iterator != drawables.end(); iterator++)
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
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin(); iterator != drawables.end(); iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				return true;
			}
		}
	}
	return false;
}

int Pong::getDrawingLayer(Drawable* obj)
{
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin(); iterator != drawables.end(); iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				iterator -> first;
			}
		}
	}
	return 0;
}

int Pong::run( int argc, char *argv[] )
{
	srand((unsigned int) time(NULL));

	// perform various OpenGL initializations
    glutInit( &argc, argv );

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - view_width / 2;
		h = h / 2 - view_height / 2;
	}

    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( view_width, view_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );                  // window title

    glClearColor( 0, 0, 0, 1.0 );                 // use black for glClear command

	glutIgnoreKeyRepeat(1);

    // callback routines
    glutDisplayFunc( *::display );                         // how to redisplay window
    glutReshapeFunc( *::reshape );                         // how to resize window
    glutKeyboardFunc( *::keyDown );                       // how to handle key presses
	glutKeyboardUpFunc( *::keyUp );
	glutSpecialFunc( *::keySpecialDown );
	glutSpecialUpFunc( *::keySpecialUp );
    glutMouseFunc( *::mouseclick );                        // how to handle mouse events
	glutTimerFunc(0, *::step, 0);

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
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
	for (it_type iterator = drawables.begin(); iterator != drawables.end(); iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			d->draw();
		}
	}

	// flush graphical output
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

    // orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
	if (w > h * ratio)                  // use width:height aspect ratio to specify view extents
	{
		scale = (double) h / (double) view_height;
		gluOrtho2D( 0 - ((w / scale) - view_width) / 2, view_width + ((w / scale) - view_width) / 2, 0, view_height );
	}
	else
	{
		scale = (double) w / (double) view_width;
		gluOrtho2D( 0, view_width, 0 - ((h / scale) - view_height) / 2, view_height + ((h / scale) - view_height) / 2 );
	}
    glViewport( 0, 0, w, h );           // adjust viewport to new window

    // switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Pong::keyDown(unsigned char key, int x, int y)
{
	// keypresses
	const int EscapeKey = 27;
	const int space = 32;

    // process keypresses
    switch ( key )
    {
	    // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;

		case space:
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

        // handles paddle movement
        default:
			game->keyDownEvent(key);
            //glutPostRedisplay();
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
	// correct for upside-down screen coordinates
    y = view_height - y;

    // handle mouse click events
    switch ( button )
    {
        case GLUT_LEFT_BUTTON:              // left button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: left press at    (" << x << "," << y << ")\n";
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: left release at  (" << x << "," << y << ")\n";
            break;

        case GLUT_RIGHT_BUTTON:             // right button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: right press at   (" << x << "," << y << ")\n";
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: right release at (" << x << "," << y << ")\n";
            break;
    }
}

void Pong::step()
{
	game->step();
}

////////////////////////////////////////////////////////////////////////////////

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
	static unsigned int fps_delay = 1000 / 60;
	glutTimerFunc(fps_delay, *::step, 0);
	Pong::getInstance()->step();
	glutPostRedisplay();
}
