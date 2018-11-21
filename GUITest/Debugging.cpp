// 
// 
// 

#include "Debugging.h"

#ifdef TGH_DEBUG

void tghDbg(String s)
{
	Serial.println(s);
}
#else
void tghDbg(String s)
{

}
#endif
