#include <cmath>
#include <vector>
#include <utility>
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

void LED_Matrix::turnOff()
{
    FastLED.clear();
}

void LED_Matrix::show()
{
    FastLED.show();
}

int LED_Matrix::getNumLeds()
{
    return this->numLeds;
}

int LED_Matrix::getNumRows()
{
    return this->numRows;
}

int LED_Matrix::getNumCols()
{
    return this->numCols;
}

void LED_Matrix::setBrightness(int brightness)
{
    this->brightness = brightness;
    FastLED.setBrightness(this->brightness);
}

void LED_Matrix::fadeToBlack(uint8_t fadeBy)
{
    fadeToBlackBy(this->leds, this->numLeds, fadeBy);
}

void LED_Matrix::lightOne(int row, int col, CRGB color)
{
    // due to snake like matrix
    // even columns go down as index increases
    // odd columns go up as index increases
    if (col & 1)
        this->leds[(this->numRows - row - 1) + col * this->numRows] = color;
    else
        this->leds[row + col * this->numRows] = color;
}

void LED_Matrix::lightOneRow(int rowIndex, CRGB color)
{
    for (int i = 0; i < this->numCols; i++)
    {
        // matrix array is snake-like
        lightOne(rowIndex, i, color);
    }
}

void LED_Matrix::iterRows(CRGB color)
{
    for (int i = 0; i < this->numRows; i++)
    {
        lightOneRow(i, color);
    }

    FastLED.show();
}

void LED_Matrix::lightOneColumn(int colIndex, CRGB color, int numToFill, bool down)
{
    if (numToFill == -1)
        numToFill = this->numRows;

    for (int i = 0; i < numToFill; i++)
    {
        int rowValue = (down ? i : this->numRows - i);
        lightOne(rowValue, colIndex, color);
    }
}

void LED_Matrix::iterColumns(CRGB color)
{
    for (int i = 0; i < this->numCols; i++)
    {
        lightOneColumn(i, color);
    }

    FastLED.show();
}

// returns number of rows to fill
// audio Data is a percent
int LED_Matrix::ratioByMRows(int audioData)
{
    return (audioData * this->numRows / 100) + 1;
}

// display 3 x 5 character at (col, row)
// all points are relative to top-left
void LED_Matrix::displayChar(int row, int col, char c, CRGB color)
{
    std::vector<std::pair<int, int>> pointArray;

    switch (c)
    {
        case 'E':
            pointArray = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {3, 0}, {4, 0}, {4, 1}, {4, 2}};
            break;

        case 'T':
            pointArray = {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {2, 1}, {3, 1}, {4, 1}};
            break;

        case 'X':
            pointArray = {{0, 0}, {1, 0}, {2, 1}, {0, 2}, {1, 2}, {3, 0}, {4, 0}, {3, 2}, {4, 2}};
            break;
    }

    for (auto it = pointArray.begin(); it != pointArray.end(); it++)
    {
        lightOne(row + (*it).first, col + (*it).second, color);
    }
}

void LED_Matrix::fillGradientMatrix(CRGB* colors, int size)
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