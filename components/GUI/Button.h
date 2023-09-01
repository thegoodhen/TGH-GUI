#include "GUIElement.h"
class Button: public GUIElement
{
    public:
    Button(String _name, String _text);
    Button(String _name)=delete;
    String getType() const override;
    String getHTML() const override;
    using GUIElement::GUIElement;

};