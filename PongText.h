/***************************************************************************//**
 * @file File containing the declaration for the PongText class.
 *
 * @brief Contains the declaration for the PongText class that handles Menu
			text
*******************************************************************************/

#ifndef _PONGTEXT_H_
#define _PONGTEXT_H_

class PongText;

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include <string>
#include "Drawable.h"

using namespace std;

/***************************************************************************//**
 * @brief The PongText class handles all the text for the Menu and MenuItems
 *
 * @details This class has many basic text formates as well as a string to
				unsigned char array functions
*******************************************************************************/
class PongText : public Drawable
{
	private:
		string text;	/*!< Text that is being edited */
		int align;		/*!< alignment of text */
		double x;		/*!< text x coordinant */
		double y;		/*!< text y coordinant */
		double size;	/*!< size of text */
		int width;		/*!< width of text */
		int height;		/*!< height of text */

		/*!
		 * @brief Gets the width of a specific character in 8ths of size. Used
		 *		in width calculations and drawing
		 */
		static int char_width(char c);

		/*!
		 * @brief Gets the height of a specific character in 8ths of size. Used
		 *		in height calculations and drawing
		 */
		static int char_height(char c);

		/*!
		 * @brief Draws given char with width and height calculations
		 */
		static void draw_char(char c, double x, double y, double size);

		/*!
		 * @brief calculates the overal size of the text area
		 */
		void calc_size();

	public:
		/*!
		 * @brief Constuctor, ans isntance of a given text input
		 */
		PongText(double x, double y, double size, string text = "", int align = 1);

		/*!
		 * @brief destroys any leftover unsigned charactor arrays
		 */
		~PongText();


		/*!
		 * @brief Sets the text string of the instance
		 */
		void setText(string text);

		/*!
		 * @brief changes Position of text
		 */
		void setPosition(double x, double y);

		/*!
		 * @brief changes size of text
		 */
		void setSize(double size);

		/*!
		 * @brief changes the alignment of the output text
		 */
		void setAlignment(int align);
		

		/*!
		 * @brief returns the width of the text
		 */
		double getWidth();

		/*!
		 * @brief teturns the height of the text
		 */
		double getHeight();


		/*!
		 * @brief Draws the text
		 */
		void draw();
};

#endif