
#include <stdio.h>
#include <string.h>
#include "Matrix.h"
#include "CoolBars.h"

const int R_4x4[4][4] = 
	{ 
		{1, 1, 1, 0},
		{1, 0, 1, 0},
		{1, 1, 1, 0},
		{1, 0, 0, 1},
	};
	
const int C_4x4[4][4] = 
	{ 
		{0, 1, 1, 0},
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{0, 1, 1, 0},
	};
	
const int O_4x4[4][4] = 
	{ 
		{0, 1, 1, 0},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
	};

void PrintLetterQuadrant(int xOffset, int yOffset, const int letterQuadrantGrid[4][4]);
void PrintLetterQuadrant(int xOffset, int yOffset, const int letterQuadrantGrid[4][4])
{
	for (int x = 0; x < 4; x += 1)
	{
		for (int y = 0; y < 4; y += 1)
		{
			SetPixel(x + xOffset, y + yOffset, letterQuadrantGrid[x][y]);
		}
	}
}

void SetCountdownState(int rocketsComingUp, int camoComingUp, int overshieldComingUp, int timeUntilMinuteThreshold)
{	
	// Layout of four quadrants of 8x8 grid
	//
	//  RR     ....
	//  RR     ....
	//
	//  CC     OO
	//  CC     OO
	//
	
	// Assuming top left origin
	// Grid is 8x8, pixel indices := [0, 7]
	
	
	// Rockets
	if (rocketsComingUp != 0)
	{
		// 0, 0 offsets -> top left
		PrintLetterQuadrant(0, 0, R_4x4);
	}
	
	// Camo
	if (camoComingUp != 0)
	{
		// 0, 4 offsets -> bottom left
		PrintLetterQuadrant(0, 4, C_4x4);
	}
	
	// Overshield
	if (overshieldComingUp != 0)
	{
		// 4, 4 offsets -> bottom right
		PrintLetterQuadrant(4, 4, O_4x4);
	}
	
	// LED Time grid
	// for now just print a full grid
	for (int x = 4; x < 8; x += 1)
	{
		for (int y = 4; y < 8; y += 1)
		{
			SetPixel(x, y, 1);
		}
	}
}
