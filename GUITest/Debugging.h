// Debugging.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


void tghDbg(String s);
#define TGH_DEBUG
