#include "HtmlSerializable.h"

ssize_t IHTMLSerializable::getHTMLLength()
{
    if(htmlLength==-1)
    {
        String theHtml=getHTML();
        htmlLength=theHtml.length();
    }
    return htmlLength;
}


size_t IHTMLSerializable::getSubstring(String s, uint8_t* _outStr, size_t _maxLen, size_t _offset)
{
    size_t stringLen = s.length();

    if (_offset >= stringLen)
    {
        return 0;
    }

    // Calculate the endIndex based on _maxLen
    size_t endIndex = _offset + _maxLen;
    String sub = s.substring(_offset, endIndex); // It's okay if endIndex > stringLen, substring will handle it.
    size_t copyLength = sub.length(); // Get actual length of the substring
    

    memcpy(_outStr, sub.c_str(), copyLength);
    return copyLength;
}


size_t IHTMLSerializable::getHTMLSubstring(uint8_t* _outStr, size_t _maxLen, size_t _offset)
{
    return getSubstring(getHTML(),_outStr,_maxLen,_offset);
}
String IHTMLSerializable::getId() const
{
    return this->id;
}