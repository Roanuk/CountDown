
#include <Python.h>
#include "PythonCaller.h"
#include "Matrix.h"

void SetPixel(int x, int y, int enable)
{
	callTriInts((char*) "Adafruit_LED_Backpack.Matrix8x8", (char*) "set_pixel", x, y, enable);
}
