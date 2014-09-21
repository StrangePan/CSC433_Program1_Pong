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
	// perform various OpenGL initializations
    glutInit( &argc, argv );

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - view_width / 2;
		h = h / 2 - view_height / 2;
	}

    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( view_width, view_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );                  // window title

    glClearColor( 0, 0, 0, 1.0 );                 // use black for glClear command

    // callback routines
    glutDisplayFunc( *::display );                         // how to redisplay window
    glutReshapeFunc( *::reshape );                         // how to resize window
    glutKeyboardFunc( *::keyboard );                       // how to handle key presses
    glutMouseFunc( *::mouseclick );                        // how to handle mouse events
    glutIdleFunc( *::idle );                               // animation callback


	Board board( 0, 0, 600, 300, 16 );

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

void Pong::keyboard(unsigned char key, int x, int y)
{ }

void Pong::mouseclick(int button, int state, int x, int y)
{ }

void Pong::idle()
{ }

////////////////////////////////////////////////////////////////////////////////

void display()
{
	Pong::getInstance()->display();
}

void reshape(int w, int h)
{
	Pong::getInstance()->reshape(w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	Pong::getInstance()->keyboard(key, x, y);
}

void mouseclick(int button, int state, int x, int y)
{
	Pong::getInstance()->mouseclick(button, state, x, y);
}

void idle()
{
	Pong::getInstance()->idle();
}
