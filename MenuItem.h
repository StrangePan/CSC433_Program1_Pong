#ifndef _MENUITEM_H_
#define _MENUTEM_H_

class Menu;

#include <string>
#include "Drawable.h"
#include "PongText.h"

using namespace std;

class MenuItem : public Drawable
{
private:
	Menu* menu;
	double x;
	double y;
	double width;
	double height;
	double border;
	PongText text;

public:
	void draw();
	void setPosition( double new_x, double new_y );
	void setText( string new_text );
	void getClicked( );
};

#endif
