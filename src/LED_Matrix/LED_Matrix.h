#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <FastLED.h>

// Defaults for my purpose
#define DEFAULT_ROW_NUM 8
#define DEFAULT_COL_NUM 16
#define DEFAULT_DATA_PIN 27
#define DEFAULT_CHIPSET WS2812B
#define DEFAULT_BRIGHTNESS 20
#define DEFAULT_LED_TYPE GRB

class LED_Matrix
{
    public:
        LED_Matrix(
            int rows = DEFAULT_ROW_NUM,
            int cols = DEFAULT_COL_NUM,
            int dataPin = DEFAULT_DATA_PIN);

        ~LED_Matrix();
        void turnOff();
        void show();
        int getNumLeds();
        int getNumRows();
        int getNumCols();
        void setBrightness(int brightness);
        void fadeToBlack(uint8_t fadeBy);
        void lightOne(int row, int col, CRGB color);
        void lightOneRow(int rowIndex, CRGB color);
        void iterRows(CRGB color);
        void lightOneColumn(int colIndex, CRGB color, int numToFill = -1, bool down = true);
        void iterColumns(CRGB color);
        void displayChar(int row, int col, char c, CRGB color);
        void fillGradientMatrix(CRGB* colors, int size);
        void rainbow();

    private:
        int numRows;
        int numCols;
        int numLeds;
        CRGB* leds;
        int brightness;
};
        
#endif