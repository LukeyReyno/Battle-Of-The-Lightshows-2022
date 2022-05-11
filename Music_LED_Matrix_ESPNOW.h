#include "src/LED_Matrix/LED_Matrix.h"

#define POT_PIN 2

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

// Music Function Defines
void Bar_Visualizer(
    LED_Matrix* musicMatrix,
    struct_message data,
    CRGB::HTMLColorCode color = CRGB::AliceBlue,
    CRGB::HTMLColorCode ceilingColor = CRGB::Red
);



