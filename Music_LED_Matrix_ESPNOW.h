#include "src/LED_Matrix/LED_Matrix.h"

#define POT_PIN 2

// set up matrix
LED_Matrix musicMatrix;

const int MY_PACKET_VERSION = 2;    //only processes verion 1 packets

volatile boolean newData=false;

int testIter = 0;

// Must match the transmitter structure
typedef struct struct_message
{
    byte  packetVersion;
    byte  pattern;
    byte  brightness;
    byte  monoAverage;
    byte  softpot;
    byte  channelData[7];
} struct_message;

// Create a struct_message called myData
struct_message myData;

const int PEAK_DELAY      = 800; //milliseconds
int LEDSOn;
int peakLED;
int peakTimeout;

//VU
DEFINE_GRADIENT_PALETTE(roundabout){
      0, 255,   0,   0,
     85,   0, 255,   0,
    170,   0,   0, 255,
    255, 255,   0,   0
};
CRGBPalette16 ripplePalette = roundabout;

DEFINE_GRADIENT_PALETTE(RGB_VU){
      0,   0, 255,   0,
    125,   0, 255,   0,
    150, 255, 255,   0,
    187, 255,   0,   0,
    255, 255,   0,   0
};
CRGBPalette16 rgbPalette = RGB_VU;

DEFINE_GRADIENT_PALETTE(BLUE_VU){
      0,   0,   0, 255,
    100,   0,   0, 255,
    175, 255, 255, 255,
    255, 255, 255, 255
};
CRGBPalette16 bluePalette = BLUE_VU;

DEFINE_GRADIENT_PALETTE(RED_VU){
      0, 255,   0,   0,
    100, 255,   0,   0,
    175, 255, 255, 255,
    255, 255, 255, 255
};
CRGBPalette16 redPalette = RED_VU;

DEFINE_GRADIENT_PALETTE(GREEN_VU){
      0,   0, 255,   0,
    100,   0, 255,   0,
    175, 255, 255, 255,
    255, 255, 255, 255
};
CRGBPalette16 greenPalette = GREEN_VU;
