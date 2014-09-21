#ifndef _PONG_H_
#define _PONG_H_

class Pong;

using namespace std;

#include <string>
#include <map>
#include <list>
#include <gl/freeglut.h>

#include "PongGame.h"
#include "Drawable.h"

class Pong
{
	private:
		static Pong* instance;
		int view_width;
		int view_height;
		int window_width;
		int window_height;
		string window_name;
		
		PongGame* game;
		map<int, list<Drawable*>> drawables;

	public:
		static const int unit;

		Pong ( );
		~Pong ( void );

		static Pong* getInstance( );
		int run ( int argc, char *argv[] );
		PongGame* getGame();

		void drawObject(Drawable* obj, int layer = 0);
		void setDrawingLayer(Drawable* obj, int layer);
		void stopDrawingObject(Drawable* obj);
		void stopDrawingAll();
		bool isDrawingObject(Drawable* obj);
		int getDrawingLayer(Drawable* obj);

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
