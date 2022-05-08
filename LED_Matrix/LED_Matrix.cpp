#include <cmath>
#include "LED_Matrix.h"

LED_Matrix::LED_Matrix(
            int rows,
            int cols,
            int dataPin)
{
    this->numRows = rows;
    this->numCols = cols;
    this->numLeds = this->numRows * this->numCols;
    this->leds = new CRGB[this->numLeds];
    this->brightness = DEFAULT_BRIGHTNESS;

    FastLED.addLeds<WS2812B, DEFAULT_DATA_PIN, GRB>(this->leds, this->numLeds);
    FastLED.setBrightness(this->brightness);
}

LED_Matrix::~LED_Matrix()
{
    delete [] this->leds;
}

int LED_Matrix::getNumLeds()
{
    return this->numLeds;
}

void LED_Matrix::lightOne(int row, int col, CRGB::HTMLColorCode color)
{
    // due to snake like matrix
    // even columns go down as index increases
    // odd columns go up as index increases
    if (col & 1)
        this->leds[(this->numRows - row - 1) + col * this->numRows] = color;
    else
        this->leds[row + col * this->numRows] = color;
    
    FastLED.show();
}

void LED_Matrix::lightOneRow(int rowIndex, CRGB::HTMLColorCode color)
{
    for (int i = 0; i < this->numCols; i++)
    {
        // matrix array is snake-like
        lightOne(rowIndex, i, color);
    }

    FastLED.show();
}

void LED_Matrix::iterRows(CRGB::HTMLColorCode color)
{
    for (int i = 0; i < this->numRows; i++)
    {
        lightOneRow(i, color);
    }

    FastLED.show();
}

void LED_Matrix::lightOneColumn(int colIndex, CRGB::HTMLColorCode color)
{
    for (int i = 0; i < this->numRows; i++)
    {
        //this->leds[i + colIndex * this->numRows] = color;
        lightOne(i, colIndex, color);
    }

    FastLED.show();
}

void LED_Matrix::iterColumns(CRGB::HTMLColorCode color)
{
    for (int i = 0; i < this->numCols; i++)
    {
        lightOneColumn(i, color);
    }

    FastLED.show();
}

void LED_Matrix::fillGradientMatrix(CRGB::HTMLColorCode* colors, int size)
{
    switch (size)
    {
        case 1:
            fill_gradient_RGB(this->leds, this->numLeds, colors[0], CRGB::Black);
            break;
        case 2:
            fill_gradient_RGB(this->leds, this->numLeds, colors[0], colors[1]);
            break;
        case 3:
            fill_gradient_RGB(this->leds, this->numLeds, colors[0], colors[1], colors[2]);
            break;
        case 4:
            fill_gradient_RGB(this->leds, this->numLeds, colors[0], colors[1], colors[2], colors[3]);
            break;
    }

    FastLED.show();
}

void LED_Matrix::rainbow()
{
    fill_rainbow(this->leds, this->numLeds, 0, 255 / this->numLeds);
    FastLED.show();
}