
#ifndef MAIN_FUNCTIONS_INCLUDE
#define MAIN_FUNCTIONS_INCLUDE
#define CHANNELS 2
#define RUNNING 1
#define READY 0
#include <sys/types.h>
void checkChannels(pid_t channelPids[], int channelStatus[]);
void runGame(int map, int channel);
#endif		
