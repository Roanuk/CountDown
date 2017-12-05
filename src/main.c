
#include <Python.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "PythonCaller.h"

/*
 * This program will manage countdowns for Halo CE PowerUp Spawns
 *  main is an infinite loop that will allow map selection
 * 	once a map is selected by scrolling to it and pressing start
 * 		a run countdown method will begin to keep track of time
 * 		as well as percent cooldown remaining for each powerup
*/

const char* maps[5] = 
	{ 
		"Chill Out",
		"Damnation", 
		"Derelict", 
		"Hang 'Em High", 
		"Prisoner" 
	};

const char* powers[4] = 
	{ "Rocks", "Snipe", "Camo", "Ovy" };

const int cools[5][4] = 
	{ 
		{120, 30, 120, 60}, 
		{120, 30, 60, 60}, 
		{75, 30, 60, 60}, 
		{120, 30, 60, 60}, 
		{120, 30, 60, 60} 
	};
 
int main(int argc, char **argv)
{
 	char* outBuf[] = {"Pick an Option", "->Map Selection"}; 
 	init();
	while(1)
	{
		mapSelection();
		break;
	}
	end();
} 

void mapSelection()
{			
	char* outBuf[] = {"Pick an Option", "->Map"}; 
	int map = 0;
	while(1)
	{
		countGame(map);
		map = map+1;
		break;
	}
}

void countGame(int map)
{
	callString((char*)"pythonTest", (char*)"someFunction", (char*)"something new");
	callTriInts((char*)"pythonTest", (char*)"someNewFunction", 1, 2, 3);
}
