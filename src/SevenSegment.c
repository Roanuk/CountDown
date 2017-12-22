
#include <Python.h>
#include "PythonCaller.h"
#include "SevenSegment.h"

void SetDigits(char* fourDigitTime)
{
	callString((char*)"Adafruit_LED_Backpack.SevenSegment", (char*)"print_number_str", fourDigitTime);
}

void SetColon(int enable)
{
	callInt((char*)"Adafruit_LED_Backpack.SevenSegment",(char*)"set_colon", enable);
}


