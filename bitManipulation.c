/*********************************************************************************************************
MIT License

Copyright (c) 2012 Samira C. Oliva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

The Program simulats a theater stage has a set of computer controlled lights.  There are 16
theater lights hand working the lights can run your program.

Professor Delia-Manuela Gârbacea

CIS 26B - Advanced C Programming
Lab #4

Written by: Samira C. Oliva

31 May 2012
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sami.h"  //switch to samira.h to run with gcc

void printMenu();
void getUserOption(unsigned short** lights, unsigned short** overLayPattern,int *startBit, int *numBits);
void turnOnAllLights(unsigned short** lights);
void turnOnARangeOfLights(unsigned short** lights, int startBit, int numBits);
void turnOffAllLights(unsigned short** lights);
void turnOffARangeOfLights(unsigned short** lights, int startBit, int numBits);
void overLayOnOffPatternOntoLightConfig(unsigned short** lights,
                                        unsigned short **overLayPattern, int starBit, int numBits);
void printBits(unsigned short wrd);
int  testBit(unsigned short wrd, int bit_to_test);
void getOverlayPatternAndStartBit(unsigned short **overLayPattern, int *startBit, int *numBits);
void freeMemory(unsigned short* lights, unsigned short* overLayPattern,int *startBit, int *numBits);

#define FLUSH while( getchar() != '\n')


int main(void)
{
    
    unsigned short  *stageLights, *overLayPattern;
    int             *startBit, *numBits;
    
    stageLights    = (unsigned short*)Malloc(sizeof(unsigned short));
    overLayPattern = (unsigned short*)Malloc(sizeof(unsigned short));
    startBit       = (int *)Malloc(sizeof(int));
    numBits        = (int *)Malloc(sizeof(int));
    
    printMenu();
    getUserOption(&stageLights, &overLayPattern, startBit, numBits);
    freeMemory(stageLights, overLayPattern, startBit, numBits);
    
    
    return 0;
}


//------------------------------------------------------------------------
void printMenu()
{
    printf("\n\nPlease select an option from the following menu\n\n");
    printf("----------------------------------------------------------------------\n");
    printf(": 1)  turn on all lights                                             :\n");
    printf(": 2)  turn on center stage lights (lights 5-10)                      :\n");
    printf(": 3)  turn on left stage lights (lights 11-15)                       :\n");
    printf(": 4)  turn on right stage lights (lights 0-4)                        :\n");
    printf(": 5)  turn off all lights                                            :\n");
    printf(": 6)  turn off center stage lights                                   :\n");
    printf(": 7)  turn off left stage lights                                     :\n");
    printf(": 8)  turn off right stage lights                                    :\n");
    printf(": 9)  overlay on/off pattern onto light configuration                :\n");
    printf(": 10) stop printing the menu                                         :\n");
    printf(": 11) print the menu again                                           :\n");
    printf(": 12) quit the menu                                                  :\n");
    printf("----------------------------------------------------------------------\n\n");
    
}

//------------------------------------------------------------------------
// Functions gets prompts the user for their option listed on the menu
// from printMenu() printed prior to this function
//
// pre:   stage lights UH
//
// post:  performs a number of operations on the stage lights by calling
//        the appropriate function while user is willing to do so
//
//void getUserOption(unsigned short* lights)
void getUserOption(unsigned short** lights, unsigned short** overLayPattern, int *startBit, int *numBits)
{
    int             userOption, endProgram, emptyReply;
    char            buffer[128], *line,  *endPtr, printFlag;
    
    printFlag  = endProgram = 1;
    emptyReply = 0;
    
    while(gets(buffer), (endProgram))
    {
        
        if(*buffer == '\0')   //if empty response
        {                       //re-prompt user
            while (*buffer == '\0')
            {
                printMenu();
                gets(buffer);
            }
        }
        
        strcat(buffer, "\n");
        line       = strtok(buffer, "\040\t\n");
        userOption = (int)strtol(line, &endPtr, 10);
        
        switch (userOption)
        {
            case 1:
                turnOnAllLights(lights);
                break;
            case 2:
                turnOnARangeOfLights(lights, 5, 6);
                break;
            case 3:
                turnOnARangeOfLights(lights, 11, 6);
                break;
            case 4:
                turnOnARangeOfLights(lights, 0, 5);
                break;
            case 5:
                turnOffAllLights(lights);
                break;
            case 6:
                turnOffARangeOfLights(lights, 5, 6);
                break;
            case 7:
                turnOffARangeOfLights(lights, 11, 6);
                
                break;
            case 8:
                turnOffARangeOfLights(lights, 0, 5);
                
                break;
            case 9:
                getOverlayPatternAndStartBit(overLayPattern, startBit, numBits);
                overLayOnOffPatternOntoLightConfig(lights, overLayPattern, *startBit, *numBits);
                break;
            case 10:
                printFlag = 0;
                break;
            case 11:
                printMenu();
                break;
            case 12:
                endProgram = 0;
                break;
            default:
                printf("Please enter a numeric value (1 - 12) from\n"
                       "the menu option\n");
                break;
        } //switch
        
        if(endProgram)
            printBits(**lights);
        if(printFlag && endProgram && emptyReply)
            printMenu();
        
    }
    
}


//------------------------------------------------------------------------
// Function tuns on all the stage lights held in an unsigned short of
// 16 bits
//
// pre: unsigned short* lights
//
// post: all of the stage lights are turned ON
//
void turnOnAllLights(unsigned short** lights)
{
    unsigned short ones = 0;
    
    ones        = ~ones;
    *(*lights) |= ones;
    
}

//------------------------------------------------------------------------
// Function turns ON a range of lights.
//      Center Stage  :  5  - 10
//      Left   Stage  :  11 - 15
//      Right  Stage  :  0  - 4
//
// pre:   unsigned short* lights
//
// post:  a given range of lights is turned ON
//
void turnOnARangeOfLights(unsigned short** lights, int startBit, int numBits)
{
    unsigned short mask;
    
    turnOffAllLights(lights);
    
    mask = (~((unsigned short) ~0 << numBits) << startBit);
    
    *(*lights) |= mask;
    
}


//------------------------------------------------------------------------
// Function turns off all the stage lights
//
// pre:  unsigned short** lights
//
// post: all of the lights are turned off
//
void turnOffAllLights(unsigned short** lights)
{
    unsigned short zero;
    
    zero        = 0;
    *(*lights) &= zero;
    
}

//------------------------------------------------------------------------
// Function turns OFF a range of lights.
//      Center Stage  :  5  - 10
//      Left   Stage  :  11 - 15
//      Right  Stage  :  0  - 4
//
// pre:   unsigned short* lights
//
// post:  a given range of lights is turned OFF
//
void turnOffARangeOfLights(unsigned short** lights, int startBit, int numBits)
{
    unsigned short mask;
    
    turnOnAllLights(lights);
    
    mask = ~(~((unsigned short) ~0 << numBits) << startBit);
    
    *(*lights) &= mask;
}


//------------------------------------------------------------------------
// Function prompts the user for the over lay pattern in binary format
// 1's and 0s as well as the start bit.
//
// pre:   nothing
//
// post:  unsigned short *overLayPattern, int *startBit, int *numBits
//        are assigned values
//
void getOverlayPatternAndStartBit(unsigned short **overLayPattern, int *startBit, int *numBits)
{
    char    buffer[128], *endPtr, *start, *pattern;
    int     valid, limit, validPattern;
    
    valid = validPattern = 0;
    
    while((!valid) || (!validPattern))
    {
        printf("\nPlease enter the over lay pattern and start bit\n"
               "example: 1011 7.\n->\n");
        gets(buffer);
        
        if(*buffer == '\0')          //if empty response
        {                            //bail-out, return to main menu
            return;
        }
        
        strcat(buffer, "\n");
        pattern  = strtok(buffer, "\040\t");
        start    = strtok(NULL, "\n");
        
        *numBits = strspn(pattern, "10");  //length of pattern binary number
        
        if((*numBits == strlen(pattern)) && ((strlen(pattern) <= 16)))
        {
            validPattern = 1;
        }
        else
        {
            validPattern = 0;
            printf("excess of lights (16 max) &| not 1's and 0's\n");
        }
        
        **overLayPattern = (unsigned short)strtol(pattern, &endPtr, 2);
        
        if(start == NULL)
        {
            printf("NULL start bit entry\n");
            valid = 0;
        }
        else
        {
            *startBit = (int)strtol(start, &endPtr, 10);
        }
        
        limit = 16 - (*startBit); //max length of over lay pattern
        
        if((*startBit >= 0) && (*startBit <= 15) && (*numBits <= limit))//0 - 15 avoid overflow
        {
            valid = 1;
        }//if_startBit
        else
        {
            valid = 0;
            printf("lack of space for pattern length &| starbit not valid\n");
        }
        
    }//_while
}

//------------------------------------------------------------------------
// Function performs the over lay pattern configuration on the stage
// lights
//
// pre:   lights, overLayPattern, starBit, numBits
//
// post:  over lay is configured onto the stage lights
//
void overLayOnOffPatternOntoLightConfig(unsigned short** lights,
                                        unsigned short **overLayPattern, int starBit, int numBits)
{
    *(*lights) &= ~( ~((unsigned short) ~0 << numBits)  << starBit);
    *(*lights) |= (*(*overLayPattern)) << starBit;
}

//------------------------------------------------------------------------
// Function with test a bit wether it is a 1 or 0
//
// pre:  the wrd unsigned short and the bit_to_test in the wrd
//
// post: returns a 1 if bit_to_test is set and 0 if it is unset
//
int  testBit(unsigned short wrd, int bit_to_test)
{
    wrd >>= bit_to_test;
    wrd &= 1;
    return wrd;
}

//------------------------------------------------------------------------
// Function prints the bits an unsigned short wrd
//
// pre:  unsigned short wrd
//
// post: bits are printed
//
void printBits(unsigned short wrd)
{
    int  testbit(unsigned short wrd, int bit_to_test);
    int  idx, bitCount, afterNbits;
    
    bitCount   = 0;
    afterNbits = 4;
    
    for (idx = 15; idx >= 0; idx--)
    {
        printf("%1d", testBit(wrd, idx));
        bitCount++;
        if(bitCount == afterNbits)
        {
            printf("\040");
            bitCount = 0;
        }
    }
    printf("\n\n");
}

//------------------------------------------------------------------------
// Deallocates any dynamically allocated memory
//
// pre:  stage lights, overLayPattern, startBit, and numBits
//
// post: stage lights, overLayPattern, startBit, and numBits are freed
//
void freeMemory(unsigned short* lights, unsigned short* overLayPattern,int *startBit, int *numBits)
{
    free(lights);
    free(overLayPattern);
    free(startBit);
    free(numBits);
}




/***
 -------- Test Runs/Output ---->
 
 // run # 1 =====================================================================
 
 Please select an option from the following menu
 
 ----------------------------------------------------------------------
 : 1)  turn on all lights                                             :
 : 2)  turn on center stage lights (lights 5-10)                      :
 : 3)  turn on left stage lights (lights 11-15)                       :
 : 4)  turn on right stage lights (lights 0-4)                        :
 : 5)  turn off all lights                                            :
 : 6)  turn off center stage lights                                   :
 : 7)  turn off left stage lights                                     :
 : 8)  turn off right stage lights                                    :
 : 9)  overlay on/off pattern onto light configuration                :
 : 10) stop printing the menu                                         :
 : 11) print the menu again                                           :
 : 12) quit the menu                                                  :
 ----------------------------------------------------------------------
 
 warning: this program uses gets(), which is unsafe.
 10
 0000 0000 0000 0000
 
 1
 1111 1111 1111 1111
 
 2
 0000 0111 1110 0000
 
 3
 1111 1000 0000 0000
 
 4
 0000 0000 0001 1111
 
 5
 0000 0000 0000 0000
 
 6
 1111 1000 0001 1111
 
 7
 0000 0111 1111 1111
 
 8
 1111 1111 1110 0000
 
 9
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 1111 0
 1111 1111 1110 1111
 
 9
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 1111 78
 lack of space for pattern length &| starbit not valid
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 1111
 excess of lights (16 max) &| not 1's and 0's
 NULL start bit entry
 lack of space for pattern length &| starbit not valid
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 11110000111100001111 3
 excess of lights (16 max) &| not 1's and 0's
 lack of space for pattern length &| starbit not valid
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 1111111111111111
 excess of lights (16 max) &| not 1's and 0's
 NULL start bit entry
 lack of space for pattern length &| starbit not valid
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 /// empty reply .: return to main menu
 1111 1111 1111 1111    /// enter option 5 (menu was turned off from
 /// printing previously
 5
 
 0000 0000 0000 0000
 
 // run # 2 ===========================================================
 
 
 
 Please select an option from the following menu
 
 ----------------------------------------------------------------------
 : 1)  turn on all lights                                             :
 : 2)  turn on center stage lights (lights 5-10)                      :
 : 3)  turn on left stage lights (lights 11-15)                       :
 : 4)  turn on right stage lights (lights 0-4)                        :
 : 5)  turn off all lights                                            :
 : 6)  turn off center stage lights                                   :
 : 7)  turn off left stage lights                                     :
 : 8)  turn off right stage lights                                    :
 : 9)  overlay on/off pattern onto light configuration                :
 : 10) stop printing the menu                                         :
 : 11) print the menu again                                           :
 : 12) quit the menu                                                  :
 ----------------------------------------------------------------------
 
 warning: this program uses gets(), which is unsafe.
 1
 1111 1111 1111 1111
 
 //empty entry
 //user is repromted
 
 Please select an option from the following menu
 
 ----------------------------------------------------------------------
 : 1)  turn on all lights                                             :
 : 2)  turn on center stage lights (lights 5-10)                      :
 : 3)  turn on left stage lights (lights 11-15)                       :
 : 4)  turn on right stage lights (lights 0-4)                        :
 : 5)  turn off all lights                                            :
 : 6)  turn off center stage lights                                   :
 : 7)  turn off left stage lights                                     :
 : 8)  turn off right stage lights                                    :
 : 9)  overlay on/off pattern onto light configuration                :
 : 10) stop printing the menu                                         :
 : 11) print the menu again                                           :
 : 12) quit the menu                                                  :
 ----------------------------------------------------------------------
 
 
 
 
 Please select an option from the following menu
 
 ----------------------------------------------------------------------
 : 1)  turn on all lights                                             :
 : 2)  turn on center stage lights (lights 5-10)                      :
 : 3)  turn on left stage lights (lights 11-15)                       :
 : 4)  turn on right stage lights (lights 0-4)                        :
 : 5)  turn off all lights                                            :
 : 6)  turn off center stage lights                                   :
 : 7)  turn off left stage lights                                     :
 : 8)  turn off right stage lights                                    :
 : 9)  overlay on/off pattern onto light configuration                :
 : 10) stop printing the menu                                         :
 : 11) print the menu again                                           :
 : 12) quit the menu                                                  :
 ----------------------------------------------------------------------
 
 
 
 // run # 3 =====================================================================
 Please select an option from the following menu
 
 ----------------------------------------------------------------------
 : 1)  turn on all lights                                             :
 : 2)  turn on center stage lights (lights 5-10)                      :
 : 3)  turn on left stage lights (lights 11-15)                       :
 : 4)  turn on right stage lights (lights 0-4)                        :
 : 5)  turn off all lights                                            :
 : 6)  turn off center stage lights                                   :
 : 7)  turn off left stage lights                                     :
 : 8)  turn off right stage lights                                    :
 : 9)  overlay on/off pattern onto light configuration                :
 : 10) stop printing the menu                                         :
 : 11) print the menu again                                           :
 : 12) quit the menu                                                  :
 ----------------------------------------------------------------------
 
 warning: this program uses gets(), which is unsafe.
 1
 1111 1111 1111 1111
 
 9
 
 Please enter the over lay pattern and start bit
 example: 1011 7.
 ->
 //user bails out
 1111 1111 1111 1111                    //previous light setting printed
 
 
 
 -------- Memory Leaks -------->
 valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./cN4exe
 
 ==578== LEAK SUMMARY:
 ==578==    definitely lost: 0 bytes in 0 blocks
 ==578==    indirectly lost: 0 bytes in 0 blocks
 ==578==      possibly lost: 0 bytes in 0 blocks
 ==578==    still reachable: 10,158 bytes in 34 blocks
 ==578==         suppressed: 0 bytes in 0 blocks
 
 
 ***/
