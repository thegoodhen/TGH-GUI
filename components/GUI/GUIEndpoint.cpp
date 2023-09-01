#include "Arduino.h"
#include "GUIEndpoint.h"

GUIEndpoint::GUIEndpoint(String _path)
{
    this->path=_path;
    this->id="ENDPOINT_"+_path;
}

String GUIEndpoint::getPath() const
{
    return path;
}

String GUIEndpoint::getType() const
{
    return "ENDPOINT";
}


String GUIEndpoint::getHeader() const
{
    return "<html><head></head><body>";
}

String GUIEndpoint::getFooter() const
{
    return "</body></html>";
}