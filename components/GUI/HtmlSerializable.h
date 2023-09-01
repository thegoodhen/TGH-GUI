#pragma once
#include <stdint.h>

#include "Arduino.h"
#include "ESPAsyncWebServer.h"

class IHTMLSerializable
{
    private:
    ssize_t htmlLength=-1;
protected:
    String id="";
public:
    virtual ~IHTMLSerializable() {}
    virtual ssize_t getHTMLLength();
    virtual size_t getHTMLSubstring(uint8_t *_outStr, size_t _maxLen, size_t _offset);
    virtual size_t getSubstring(String s, uint8_t* _outStr, size_t _maxLen, size_t _offset);
    virtual String getHTML() const = 0;
    virtual String getType() const = 0;
    virtual String getId() const;
};