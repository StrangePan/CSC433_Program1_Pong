#ifndef _PONG_H_
#define _PONG_H_

#include <iostream>
#include <string>
#include <list>
#include <gl/freeglut.h>

#include "Drawable.h"
#include "PongGame.h"

using namespace std;

class Pong
{
	private:
		static Pong* instance;
		int wWidth;
		int wHeight;
		int wTop;
		int wLeft;
		int vWidth;
		int vHeight;
		string wName;
		list<Drawable*> drawables;
		PongGame game;

	public:
		Pong ( );
		~Pong ( void );

		static Pong* getInstance( );
		int run ( int argc, char *argv[] );
		PongGame* getGame();

		void drawObject(Drawable* obj);
		void stopDrawingObject(Drawable* obj);
		void stopDrawingAll();

		int getViewWidth();
		int getViewHeight();
		
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
