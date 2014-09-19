#include "Pong.h"

void initOpenGL();

Pong::Pong()
{
	instance = this;
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
    glutInitWindowPosition( this -> wLeft, this -> wHeight );                  // initial window position
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
{ }

void Pong::reshape(int w, int h)
{ }

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
