#ifndef _PONG_H_
#define _PONG_H_

#include <iostream>
#include <string>
using namespace std;

#include <gl/freeglut.h>

class Pong
{
	private:
		static Pong* instance;
		int wWidth = 400;
		int wHeight = 300;
		int wTop = 50;
		int wLeft = 100;
		string wName = "Pong";

	public:
		Pong ( );
		~Pong ( void );
		static Pong* getInstance( );
		int run ( int argc, char *argv[] );
		
		void display();
		void reshape( int w, int h );
		void keyboard( unsigned char key, int x, int y );
		void mouseclick( int button, int state, int x, int y );
		void idle();


};

void display();
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void idle();

#endif
