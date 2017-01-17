// BluetoothModule.h

#ifndef _BLUETOOTHMODULE_h
#define _BLUETOOTHMODULE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


Stream* getBTStream();

#endif

