#include "LED_Matrix.h"

#define POT_PIN 2

int i = 0;

void setup()
{
    Serial.begin(115200);
    Serial.print("\nSerial Monitor Output for LED_Matrix_Test\n");
}

void loop()
{
    LED_Matrix myMatrix;
    uint16_t potRead = analogRead(POT_PIN);
    Serial.print("PotRead: ");
    Serial.println(potRead);

    uint8_t brightness = map(potRead, 0, 4095, 0, 150);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    myMatrix.setBrightness(brightness);

    CRGB::HTMLColorCode colors[] = {CRGB::Red, CRGB::Yellow, CRGB::Blue, CRGB::Purple};

    switch (i)
    {
        case 0:
            myMatrix.fillGradientMatrix(colors, 4);
            break;
        
        case 1:
            myMatrix.rainbow();
            break;

        case 2:
            myMatrix.lightOne(0, 4, CRGB::Red);
            myMatrix.lightOne(3, 5, CRGB::Blue);
            myMatrix.lightOne(6, 11, CRGB::Green);
            break;

        case 3:
            myMatrix.lightOneColumn(2, CRGB::Yellow);
            myMatrix.lightOneColumn(7, CRGB::Purple);
            myMatrix.lightOneColumn(13, CRGB::Red);
            break;

        case 4:
            myMatrix.iterColumns(CRGB::Aqua);
            break;

        case 5:
            myMatrix.lightOneRow(2, CRGB::Yellow);
            myMatrix.lightOneRow(7, CRGB::Purple);
            break;

        case 6:
            myMatrix.iterRows(CRGB::PeachPuff);
            break;

        default:
            i = 0;
            break;
    }

    EVERY_N_MILLISECONDS(5000)
    {
        i++;
        FastLED.clear();
    }
}