
#ifndef MAIN_FUNCTIONS_INCLUDE
#define MAIN_FUNCTIONS_INCLUDE
#define CHANNELS 2
#define RUNNING 1
#define READY 0
#include <sys/types.h>
void checkChannels(pid_t channelPids[], int channelStatus[]);
void runGame(int mapIdx, int channel);
void multiChannelExe();
void singleChannelExe();
void UpdateCoolDownDisplay(int currentGameTime, int mapIdx);
void UpdateGameTimeDisplay(int newGameTime);
int CoolProgress(int gameTime, int intervalTime);
#endif		
