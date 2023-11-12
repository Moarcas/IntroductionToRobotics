#ifndef SEGMENTDISPLAY.H
#define SEGMENTDISPLAY.H

const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;

const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

const int regSize = 8;
                    
const int displayDigits[] = {
    segD1, segD2, segD3, segD4
};

const int displayCount = 4; 
const int encodingsNumber = 11;

const int byteEncodings[encodingsNumber] = {
    //A B C D E F G DP
    B11111100, // 0
    B01100000, // 1
    B11011010, // 2
    B11110010, // 3
    B01100110, // 4
    B10110110, // 5
    B10111110, // 6
    B11100000, // 7
    B11111110, // 8
    B11110110, // 9
    B00000000, // empty disply
};

const int emptyDisplay = 10;

void writeReg(int digit, int writeDp = 0);

void writeNumberToDisplay(int number);

#endif
