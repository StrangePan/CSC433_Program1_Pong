#include "Pong.h"

Pong* Pong::instance;

Pong::Pong() : wWidth(600), wHeight(300), wTop(50), wLeft(100), vWidth(600), vHeight(300), wName("Pong")
{ }

Pong::~Pong()
{ }

Pong* Pong::getInstance()
{
	return instance;
}

PongGame* Pong::getGame()
{
	return &game;
}

void Pong::drawObject(Drawable* obj)
{
	for (Drawable* d : this->drawables)
	{
		if (d == obj) return;
	}
	this->drawables.push_back(obj);
}

void Pong::stopDrawingObject(Drawable* obj)
{
	this->drawables.remove(obj);
}

void Pong::stopDrawingAll()
{
	this->drawables.clear();
}

int Pong::run( int argc, char *argv[] )
{
	// perform various OpenGL initializations
    glutInit( &argc, argv );


    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( wWidth, wHeight);    // initial window size
    glutInitWindowPosition( wLeft, wTop );                  // initial window position
    glutCreateWindow( wName.c_str() );                  // window title

    glClearColor( 0, 0, 0, 1.0 );                 // use black for glClear command

    // callback routines
    glutDisplayFunc( *::display );                         // how to redisplay window
    glutReshapeFunc( *::reshape );                         // how to resize window
    glutKeyboardFunc( *::keyboard );                       // how to handle key presses
    glutMouseFunc( *::mouseclick );                        // how to handle mouse events
    glutIdleFunc( *::idle );                               // animation callback


    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;

}

void Pong::display()
{
	//clear the display and set backround to black
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );
    
	// Draw all registered drawables
	for (Drawable* d : this->drawables)
	{
		d->draw();
	}

	// flush graphical output
    glutSwapBuffers();
    glFlush();
}

void Pong::reshape(int w, int h)
{
	// store new window dimensions globally
    wWidth = w;
    wHeight = h;
	double ratio = (double) vWidth / (double) vHeight;
	double scale;

    // orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
	if (w > h * ratio)                  // use width:height aspect ratio to specify view extents
	{
		scale = (double) h / (double) vHeight;
		gluOrtho2D( 0 - ((w / scale) - vWidth) / 2, vWidth + ((w / scale) - vWidth) / 2, 0, vHeight );
	}
	else
	{
		scale = (double) w / (double) vWidth;
		gluOrtho2D( 0, vWidth, 0 - ((h / scale) - vHeight) / 2, vHeight + ((h / scale) - vHeight) / 2 );
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
