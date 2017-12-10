
#include <stdio.h>
#include <string.h>
#include "Matrix.h"
#include "CoolBars.h"

void SetProgress(int power, int progress)
{	
	int xOff = power * 2;
	for(int y = 0; y < 8; y += 1)
	{
		for(int x = xOff; x < xOff + 2; x += 1)
		{
			if(((x - xOff) + (y * 2)) < progress)
			{
				SetPixel(x, y, 1);
			}
			else
			{
				SetPixel(x, y, 0);
			}
		}
	}
}
