
#include <Python.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"
#include "Input.h"
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
	int map;
	int channel;
	int pid;
	pid_t channelPids[CHANNELS];
	int channelStatus[CHANNELS];
 	pythonInit();
 	int runs = 10;
	while(runs > 0)
	{		
		char* outBuf[] = {"Up/Down for Map", "L/R for Channel"}; 
		do{
			printf("Select ");	
			getSelection(&map, &channel);	
			checkChannels(channelPids, channelStatus);
		} while(channelStatus[channel] == RUNNING);
		printf("C:%d ", channel);
		pid = fork();
		if(pid == 0)
		{
			runGame(map, channel);
			return 0;
		}
		else
		{
			printf("Running %d", channel);
			channelPids[channel] = pid;
			channelStatus[channel] = RUNNING;
		}
		runs -= 1;
	}
	pythonEnd();
} 

void checkChannels(pid_t channelPids[], int channelStatus[])
{
	int status;
	for(int index = 0; index < CHANNELS; index += 1)
	{
		if(channelStatus[index] == READY)
		{
			continue;
		}
		waitpid(channelPids[index], &status, WNOHANG);
		if(WIFEXITED(status))
		{
			channelStatus[index] = READY;
		}
		else
		{
			channelStatus[index] = RUNNING;
		}
	}
}

void runGame(int map, int channel)
{
	sleep(2);
}
