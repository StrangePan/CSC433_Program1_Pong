#ifndef _MENU_H_
#define _MENU_H_

class Menu;

#include <string>
#include <list>
#include "Drawable.h"
#include "MenuItem.h"
#include "PongText.h"
#include "Pong.h"

using namespace std;

class Menu : public Drawable
{
private:
	double x;
	double y;
	double width;
	double height;
	double border;

	list<MenuItem*> items;
	PongText title;

public:
	void draw();
	void setPosition( double new_x, double new_y );
	void setTitle( string new_title );

};

#endif
