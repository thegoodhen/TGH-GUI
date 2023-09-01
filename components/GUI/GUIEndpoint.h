#include "Arduino.h"
#include "GUIContainer.h"

class GUIEndpoint:public GUIContainer
{
   public:
   GUIEndpoint(String _path);   
   String getType() const override;
   String getHeader() const override;
   String getFooter() const override;
   String getPath() const;
   private:
   String path;
};