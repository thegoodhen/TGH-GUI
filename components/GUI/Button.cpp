#include "Button.h"
#include "Arduino.h"

Button::Button(String _name, String _text):GUIElement(_name)
{
    id=_name;
    text=_text;
}

String Button::getType() const
{
    return "BUTTON";
}
String Button::getHTML() const
{
    return "<button>"+this->text+"</button>\n";
}