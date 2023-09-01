#include "GUIElement.h"
#include "HtmlSerializable.h"
#include "GUIContainer.h"
#include <cstring>
#include "Arduino.h"

int GUIContainer::add(IHTMLSerializable *_ge)
{
    if (find(_ge->getId()))
    {
        return 1;
    }
    elements.push_back(_ge);
    return 0;
}

IHTMLSerializable* GUIContainer::find(String _id)
{
    for (std::vector<int>::size_type i = 0; i != elements.size(); i++)
    {
        if (elements[i]->getType() == "CONTAINER")
        {
            IHTMLSerializable* foundElement = ((GUIContainer*)elements[i])->find(_id);
            if (foundElement) // if the container found it
            {
                return foundElement;
            }
        }
        if ((elements[i]->getId()==_id))
        {
            return elements[i];
        }
    }
    return NULL;
}

String GUIContainer::getType() const
{
    return "CONTAINER";
}

size_t GUIContainer::getHTMLSubstring(uint8_t* _outStr, size_t _maxLen, size_t _offset)
{

    String header = getHeader();
    size_t currentIndex = 0;
    size_t totalBytesCopied = 0;

    if (_offset < header.length())
    {
        totalBytesCopied += IHTMLSerializable::getSubstring(header, _outStr, _maxLen, _offset);
        _maxLen -= totalBytesCopied; 
        _outStr += totalBytesCopied;
    }
    currentIndex += header.length();

    for (std::vector<int>::size_type i = 0; i != elements.size() && _maxLen > 0; i++)
    {
        size_t currentElementLen = elements[i]->getHTMLLength();
        if (_offset >= currentIndex && _offset < currentIndex + currentElementLen)
        {
            size_t bytesCopied = elements[i]->getHTMLSubstring(_outStr, _maxLen, _offset - currentIndex);
            totalBytesCopied += bytesCopied;
            _maxLen -= bytesCopied;
            _outStr += bytesCopied;
            _offset = 0; // Reset offset for subsequent elements
        }
        currentIndex += currentElementLen;
    }

    if (_maxLen > 0)
    {
        totalBytesCopied += getSubstring(getFooter(), _outStr, _maxLen, _offset - currentIndex);
    }

    return totalBytesCopied;
}


//TODO: optimize so that we do not have to recalculate this every time!
ssize_t GUIContainer::getHTMLLength() 
{
    ssize_t len = 0;
    len += getHeader().length();
    for (std::vector<int>::size_type i = 0; i != elements.size(); i++)
    {
        len += elements[i]->getHTMLLength();
    }
    len += getFooter().length();
    return len;
}
String GUIContainer::getHTML() const
{
    return "";
}