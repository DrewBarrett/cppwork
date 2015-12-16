#include "Button.h"

Button::Button(int x1, int y1, std::string text1)
{
    x = x1;
    y = y1;
    text = text1;
    height = 20;
    width = text.size()*2;
}
