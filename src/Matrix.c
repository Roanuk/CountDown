
#include <Python.h>
#include "PythonCaller.h"
#include "Matrix.h"

void SetPixel(int x, int y, int enable)
{
	callTriInts((char*) "Matrix8x8", (char*) "set_pixel", x, y, enable);
}
