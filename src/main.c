
#include <stdio.h>
#include "../include/main.h"

/*
 * This program will manage countdowns for Halo CE PowerUp Spawns
 *  main is an infinite loop that will allow map selection
 * 	once a map is selected by scrolling to it and pressing start
 * 		a run countdown method will begin to keep track of time
 * 		as well as percent cooldown remaining for each powerup
*/
 
int main(int argc, char **argv)
{
	char* outBuf[2]; 
	while(1)
	{
		outBuf[0] = "Pick an Option";
		outBuf[1] = "->Map Selection";
		mapSelection();
	}
} 

void mapSelection()
{
	static const char* maps[5] = 
		{ 
			"Chill Out",
			"Damnation", 
			"Derelict", 
			"Hang 'Em High", 
			"Prisoner" 
		};
	static const char* powers[4] = 
		{ "Rocks", "Snipe", "Camo", "Ovy" };
	static const int cools[5][4] = 
		{ 
			{120, 30, 120, 60}, 
			{120, 30, 60, 60}, 
			{75, 30, 60, 60}, 
			{120, 30, 60, 60}, 
			{120, 30, 60, 60} 
		};
		
	char* outBuf[2]; 
	int map = 0;
	while(1)
	{
		outBuf[0] = "Pick a Map";
		outBuf[1] = "->" + maps[map];
		countGame(map, cools[map]);
		map = map+1;
	}
}

void countGame(int map, int[4] cools)
{
	
}
