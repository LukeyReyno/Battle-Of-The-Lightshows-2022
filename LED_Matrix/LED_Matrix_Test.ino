#include "LED_Matrix.h"

void setup()
{
    
}

void loop()
{
    LED_Matrix myMatrix;

    CRGB::HTMLColorCode colors[] = {CRGB::Red, CRGB::Yellow, CRGB::Blue, CRGB::Purple};
    myMatrix.fillGradientMatrix(colors, 4);
    //myMatrix.rainbow();
    delay(5000);
    FastLED.clear();

    myMatrix.lightOne(0, 4, CRGB::Red);
    myMatrix.lightOne(3, 5, CRGB::Blue);
    myMatrix.lightOne(6, 11, CRGB::Green);
    delay(5000);
    FastLED.clear();

    myMatrix.lightOneColumn(2, CRGB::Yellow);
    myMatrix.lightOneColumn(7, CRGB::Purple);
    myMatrix.lightOneColumn(13, CRGB::Purple);
    delay(5000);
    FastLED.clear();

    myMatrix.iterColumns(CRGB::Aqua);
    delay(5000);
    FastLED.clear();

    myMatrix.lightOneRow(2, CRGB::Yellow);
    myMatrix.lightOneRow(7, CRGB::Purple);
    delay(5000);
    FastLED.clear();

    myMatrix.iterRows(CRGB::Aqua);
    delay(5000);
    FastLED.clear();
}