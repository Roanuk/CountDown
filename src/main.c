
#include <Python.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"
#include "Input.h"
#include "PythonCaller.h"
#include "SevenSegment.h"
#include "CoolBars.h"

/*
 * This program will manage countdowns for Halo CE PowerUp Spawns
 *  main is an infinite loop that will allow map selection
 * 	once a map is selected by scrolling to it and pressing start
 * 		a run countdown method will begin to keep track of time
 * 		as well as percent cooldown remaining for each powerup
*/
#define NumOfMaps 5
const char* maps[NumOfMaps] = 
	{ 
		"Chill Out",
		"Damnation", 
		"Derelict", 
		"Hang 'Em High", 
		"Prisoner" 
	};

#define NumOfCools 4
const char* powers[NumOfCools] = 
	{ "Rocks", "Snipe", "Camo", "Ovy" };

const int cools[NumOfMaps][NumOfCools] = 
	{ 
		{120, 30, 120, 60}, 
		{120, 30, 60, 60}, 
		{75, 30, 60, 60}, 
		{120, 30, 60, 60}, 
		{120, 30, 60, 60} 
	};
	 
int main(int argc, char **argv)
{
 	pythonInit();
 	int runs = 1;
	while(runs > 0)
	{		
		char* outBuf[] = {"Up/Down for Map", "L/R for Channel"}; 
		//singleChannelExe();
		test();
		runs -= 1;
	}
	pythonEnd();
} 

void singleChannelExe()
{
	runGame(0,0);
}

void runGame(int map, int channel)
{
	int endTime = 200;
	int gameTime = 0;
	//SetColon(1);
	while(gameTime < endTime)
	{
		//CoolDownDisplay(gameTime, map);
		//GameTimeDisplay(gameTime);
		sleep(1);
		gameTime += 1;
	}
}

void GameTimeDisplay(int gameTime)
{
	const int DigitCount = 4;
	char printTime[DigitCount];
	
	int game10Min = (gameTime / 60) / 10;
	int gameMin = (gameTime / 60) % 10;
	int game10Sec = (gameTime % 60) / 10;
	int gameSec = (gameTime % 60) % 10;
	sprintf(printTime, "%d%d%d%d", game10Min, gameMin, game10Sec, gameSec);
	SetDigits(printTime);
}

void CoolDownDisplay(int gameTime, int map)
{
	for(int power = 0; power < NumOfCools; power += 1)
	{
		SetProgress(power, CoolProgress(gameTime, cools[map][power]));
	}
}


int CoolProgress(int gameTime, int intervalTime)
{
	if(intervalTime == 0)
	{
		return 0;
	}
	
	const int CoolSize = 16;
	int progress = (((gameTime % intervalTime) * CoolSize) / intervalTime) + 1;
	
	if(progress > CoolSize)
	{
		return CoolSize;
	}
	else if(progress > 0)
	{
		return progress;
	}
	else
	{
		return 0;
	}	
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

void multiChannelExe()
{	
	int map;
	int channel;
	int pid;
	static pid_t channelPids[CHANNELS];
	static int channelStatus[CHANNELS];
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
		exit(0);
	}
	else
	{
		printf("Running %d", channel);
		channelPids[channel] = pid;
		channelStatus[channel] = RUNNING;
	}
}
