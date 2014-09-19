#include "Pong.h"

void initOpenGL();

Pong::Pong()
{ }

Pong::~Pong()
{ }

int Pong::run( int argc, char *argv[] )
{
	// perform various OpenGL initializations
    glutInit( &argc, argv );


    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );     // 32-bit graphics and single buffering

    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 100, 50 );                  // initial window position
    glutCreateWindow( "OpenGL Demo" );                  // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );                 // use black for glClear command

    // callback routines
    glutDisplayFunc( display );                         // how to redisplay window
    glutReshapeFunc( reshape );                         // how to resize window
    glutKeyboardFunc( keyboard );                       // how to handle key presses
    glutMouseFunc( mouseclick );                        // how to handle mouse events
    glutIdleFunc( idle );                               // animation callback


    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;

}
