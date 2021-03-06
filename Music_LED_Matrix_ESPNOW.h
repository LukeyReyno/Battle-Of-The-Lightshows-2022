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
    CRGB color = CRGB::AliceBlue,
    CRGB ceilingColor = CRGB::Red
);

void Bar_Visualizer_blue_wave(
    LED_Matrix* musicMatrix,
    struct_message data,
    CRGB color,
    CRGB ceilingColor
);

void floating_dots(LED_Matrix* musicMatrix, CRGB dotColor);
