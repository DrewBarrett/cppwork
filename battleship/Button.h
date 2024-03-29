#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_color.h>

class Button
{
public:
	/** Default constructor */
	Button(int, int, std::string);
	void draw(ALLEGRO_MOUSE_STATE);
	int checkMouse(ALLEGRO_MOUSE_STATE);
	int Getx() { return x; }
	/** Set x
	 * \param val New value to set
	 */
	void Setx(int val) { x = val; }
	/** Access y
	 * \return The current value of y
	 */
	int Gety() { return y; }
	/** Set y
	 * \param val New value to set
	 */
	void Sety(int val) { y = val; }
	/** Access text
	 * \return The current value of text
	 */
	std::string Gettext() { return text; }
	/** Set text
	 * \param val New value to set
	 */
	void Settext(std::string val) { text = val; }
	/** Access width
	 * \return The current value of width
	 */
	int Getwidth() { return width; }
	/** Set width
	 * \param val New value to set
	 */
	void Setwidth(int val) { width = val; }
	/** Access height
	 * \return The current value of height
	 */
	int Getheight() { return height; }
	/** Set height
	 * \param val New value to set
	 */
	void Setheight(int val) { height = val; }
protected:
private:
	ALLEGRO_FONT *font;
	int x; //!< Member variable "x"
	int y; //!< Member variable "y"
	std::string text; //!< Member variable "text"
	int width; //!< Member variable "width"
	int height; //!< Member variable "height"
	ALLEGRO_COLOR color;
};

#endif // BUTTON_H
