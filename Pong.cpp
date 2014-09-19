#include "Pong.h"

const float White[]     = { 1.0, 1.0, 1.0 };

Pong* Pong::instance;

const float ViewplaneSize = 1000.0;

Pong::Pong()
{

	instance = this;
	wWidth = 400;
	wHeight = 300;
	wTop = 50;
	wLeft = 100;
	wName = "Pong";

}

Pong::~Pong()
{ }

Pong* Pong::getInstance()
{
	return instance;
}

int Pong::run( int argc, char *argv[] )
{
	// perform various OpenGL initializations
    glutInit( &argc, argv );


    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( this -> wWidth, this -> wHeight);    // initial window size
    glutInitWindowPosition( this -> wLeft, this -> wTop );                  // initial window position
    glutCreateWindow( this -> wName.c_str() );                  // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );                 // use black for glClear command

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

	glColor3fv( White );
    glBegin( GL_LINES );
        glVertex2f( 0, -1000 );
        glVertex2f( 0, 1000 );
    glEnd();

	glColor3fv( White );
    glBegin( GL_LINES );
        glVertex2f( -1000, -1000 );
        glVertex2f( 1000, -1000 );
    glEnd();

	glColor3fv( White );
    glBegin( GL_LINES );
        glVertex2f( -1000, 999 );
        glVertex2f( 1000, 999 );
    glEnd();

	// flush graphical output
    glutSwapBuffers();
    glFlush();
}

void Pong::reshape(int w, int h)
{
	// store new window dimensions globally
    wWidth = w;
    wHeight = h;

    // orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > h )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( -ViewplaneSize * w / h, ViewplaneSize * w / h, -ViewplaneSize, ViewplaneSize );
    else
        gluOrtho2D( -ViewplaneSize, ViewplaneSize, -ViewplaneSize * h / w, ViewplaneSize * h / w );
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
