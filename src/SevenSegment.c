
#include <Python.h>
#include "PythonCaller.h"
#include "SevenSegment.h"

void SetDigits(char* fourDigitTime)
{
	callString((char*)"SevenSegment", (char*)"print_number_str", fourDigitTime);
}

void SetColon(int enable)
{
	callInt((char*)"SevenSegment",(char*)"set_colon", enable);
}


