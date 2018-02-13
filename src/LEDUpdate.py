import Adafruit_LED_Backpack
from Adafruit_LED_Backpack import Matrix8x8
from Adafruit_LED_Backpack import SevenSegment
import sys

# Constant arrays for display Power-Up insignia
R_4x4 = [[1, 1, 1, 0], [1, 0, 1, 0], [1, 1, 1, 0], [1, 0, 0, 1]]
C_4x4 = [[0, 1, 1, 0], [1, 0, 0, 0], [1, 0, 0, 0], [0, 1, 1, 0]]
O_4x4 = [[0, 1, 1, 0], [1, 0, 0, 1], [1, 0, 0, 1], [0, 1, 1, 0]]


def getopts(argv):
    opts = {} # Empty dictionary to store key-value pairs
    while argv: # while there are arguments left to parse..
        if argv[0][0] == '-': # Found a "-name value" pair.
            opts[argv[0]] = argv[1]  # Add key and value to the dictionary
            argv = argv[2:] # Trim the first two elements of the list by copying it starting from idx 2
        else:
            opts[argv[0]] = 0 # otherwise just store off the key and a bogus value of 0
            argv = argv[1:] # Trim just the first element of the list since that's all we processed
    return opts

def printLetterQuadrant(dotDisplay, xOffset, yOffset, gridToPrint):
    for x in range(4):
        for y in range(4):
            dotDisplay.set_pixel(x + xOffset, y + yOffset, gridToPrint[y][x])
            
def printTimeQuadrant(dotDisplay, xOffset, yOffset, time):
    currentTime = 1
    for x in range(4):
        for y in range(4):
            if (currentTime <= time):
                dotDisplay.set_pixel(7 - y, x, 1);
                currentTime += 1
            else:
                break
            
def printClockTimeSec(clockDisplay, timeElapsedSec):
    clockDisplay.set_colon(1)
    minElapsed = (timeElapsedSec - timeElapsedSec % 60) / 60
    if (minElapsed <= 99):
        remainderSec = timeElapsedSec - minElapsed * 60
    else:
        minElapsed = 99
        remainderSec = 99
    
    min = str(minElapsed)
    sec = str(remainderSec)
    
    # Print minute display
    if (min == '0'):
        min = 0 # do nothing basically
    elif (len(min) > 1):
        clockDisplay.set_digit(0, min[0])
        clockDisplay.set_digit(1, min[1])
    else:
        clockDisplay.set_digit(1, min[0])
        
    # Print second display
    if (remainderSec == 0):
        clockDisplay.set_digit(2, 0);
        clockDisplay.set_digit(3, 0);
    elif (len(sec) > 1):
        clockDisplay.set_digit(2, sec[0])
        clockDisplay.set_digit(3, sec[1])
    else:
        clockDisplay.set_digit(2, 0)
        clockDisplay.set_digit(3, sec[0])
        

# args: ['-r']='0'/'1', ['-c']='0'/'1', ['-o']='0'/'1'
def updateDisplays(args):
    dotDisplay = Matrix8x8.Matrix8x8(address=0x71, busnum=1)
    dotDisplay.begin()
    dotDisplay.clear()
    
    if '+r' in args:
        printLetterQuadrant(dotDisplay, 0, 0, R_4x4)
    if '+c' in args:
        printLetterQuadrant(dotDisplay, 0, 4, C_4x4)
    if '+o' in args:
        printLetterQuadrant(dotDisplay, 4, 4, O_4x4)
    if '-t' in args:
        t = int(args['-t'])
        if t >= 1 and t <= 16:
            printTimeQuadrant(dotDisplay, 0, 4, t);
    
    clockDisplay = SevenSegment.SevenSegment()
    clockDisplay.begin()
    clockDisplay.clear()
    
    if '-gt' in args:
        gameTime = int(args['-gt'])
        printClockTimeSec(clockDisplay, gameTime)
    
    # Flush to both displays at the same time
    dotDisplay.write_display()
    clockDisplay.write_display()
    
    return;

if __name__ == '__main__':
    from sys import argv
    parsedArgs = getopts(argv)
    
    updateDisplays(parsedArgs)
    
    # print("you are in main!");
    # testDisplay();
    