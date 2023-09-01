#include "GUIElement.h"
#include "HtmlSerializable.h"
#include "Arduino.h"
#include <vector>
#pragma once

class GUIContainer : public IHTMLSerializable
{
public:
    String getType() const override;
    IHTMLSerializable* find(String _id);
    virtual int add(IHTMLSerializable* _ge);
    virtual String getHeader() const = 0;
    virtual String getFooter() const = 0;
    ssize_t getHTMLLength() override;
    String getHTML() const override;
    size_t getHTMLSubstring(uint8_t* _outStr, size_t _maxLen, size_t _offset) override;
    //virtual int sendHeader(AsyncWebServerRequest* _request);
    //virtual int sendFooter(AsyncWebServerRequest* _request);

private:
    std::vector<IHTMLSerializable*> elements;
};