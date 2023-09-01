#include "Arduino.h"
#include "HtmlSerializable.h"
#pragma once
#define MAX_NAME_LENGTH 20
class GUIElement:public IHTMLSerializable
{
public:
    GUIElement(String name);
protected:
String text;

};