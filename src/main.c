
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"
#include "Input.h"
#include "SevenSegment.h"
#include "CoolBars.h"

/*
 * This program will manage countdowns for Halo CE PowerUp Spawns
 *  main is an infinite loop that will allow map selection
 * 	once a map is selected by scrolling to it and pressing start
 * 		a run countdown method will begin to keep track of time
 * 		as well as percent cooldown remaining for each powerup
*/
#define MapCount 5
const char* mapNames[MapCount] = 
	{ 
		"Chill Out",
		"Prisoner",
		"Hang 'Em High",
		"Derelict",
		"Damnation",
	};

#define CoolDownCount 4
#define UsedCooldownsCount 3
const int mapCooldowns[MapCount][CoolDownCount] = 
	{ 
		// R:=Rockets,  C:=Camo,  O:=Overshield,  S:=Sniper(unused)
		//R    C   O    S
		{120, 120, 60, 30}, // Chilly
		{120, 60, 60, 30}, // Pris
		{120, 60, 60, 30}, // Hang em; note that OV alternates with a Camo on this map, as "top powerup"
		{75, 60, 60, 30}, // Derry
		{120, 60, 60, 30},  // Dammy
	};

// Note these constants should be in sync with the cooldown grid above
#define RocketCooldownIndex 0
#define CamoCooldownIndex 1
#define OvershieldCooldownIndex 2
	 
int main(int argc, char **argv)
{
 	int runs = 1;
	while (runs > 0)
	{		
		char* outBuf[] = {"Up/Down for Map", "L/R for Channel"}; 
		singleChannelExe();
		// SetDigits("0000");
		runs -= 1;
	}
} 

void singleChannelExe()
{
	runGame(0,0);
}

void runGame(int mapIdx, int channel)
{
	int endTime = 99 * 60 + 59; // 99:59
	int currentGameTime = 0;
	//SetColon(1);
	while (currentGameTime < endTime)
	{
		UpdateCoolDownDisplay(currentGameTime, mapIdx);
		UpdateGameTimeDisplay(currentGameTime);
		sleep(1);
		currentGameTime += 1;
	}
}

void UpdateGameTimeDisplay(int newGameTime)
{
	const int DigitCount = 4;
	char printTime[DigitCount];
	
	int game10Min = (newGameTime / 60) / 10;
	int gameMin = (newGameTime / 60) % 10;
	int game10Sec = (newGameTime % 60) / 10;
	int gameSec = (newGameTime % 60) % 10;
	sprintf(printTime, "%d%d%d%d", game10Min, gameMin, game10Sec, gameSec);
	SetDigits(printTime);
}

void UpdateCoolDownDisplay(int currentGameTime, int mapIdx)
{
	int secUntilNextMinuteMark = 60 - (currentGameTime % 60);
	int coolDownComingUpTracking[UsedCooldownsCount];
	
	for (int cooldownIdx = 0; cooldownIdx < UsedCooldownsCount; cooldownIdx += 1)
	{
		coolDownComingUpTracking[cooldownIdx] = 1; // hardcoding to ON right now
		
		// Actually need to be referencing the CD intervals indicated in the mapCooldowns matrix, %'ing by 60,
		// and seeing if the CD is coming up this minute (or something like that), and then setting
		// coolDownComingUpTracking[cooldownIdx] accordingly
	}
	
	SetCountdownState(
		coolDownComingUpTracking[RocketCooldownIndex],
		coolDownComingUpTracking[CamoCooldownIndex],
		coolDownComingUpTracking[OvershieldCooldownIndex],
		secUntilNextMinuteMark
		);
}

// TO-DO, delete this. saving for now for reference for how to calculate intervals
int CoolProgress(int gameTime, int intervalTime)
{
	if (intervalTime == 0)
	{
		return 0;
	}
	
	const int CoolSize = 16;
	int progress = (((gameTime % intervalTime) * CoolSize) / intervalTime) + 1;
	
	if (progress > CoolSize)
	{
		return CoolSize;
	}
	else if (progress > 0)
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
	for (int index = 0; index < CHANNELS; index += 1)
	{
		if (channelStatus[index] == READY)
		{
			continue;
		}
		waitpid(channelPids[index], &status, WNOHANG);
		if (WIFEXITED(status))
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
	} while (channelStatus[channel] == RUNNING);
	printf("C:%d ", channel);
	pid = fork();
	if (pid == 0)
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
