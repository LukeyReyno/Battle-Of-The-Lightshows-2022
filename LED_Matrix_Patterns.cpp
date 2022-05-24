#include "LED_Matrix_Patterns.h"

void three_col_wave_text(LED_Matrix* myMatrix)
{
    uint8_t sinBeat = beatsin8(10, 0, myMatrix->getNumCols() - 1, 0, 0);
    uint8_t sinBeat2 = beatsin8(15, 0, myMatrix->getNumCols() - 1, 0, 85);
    uint8_t sinBeat3 = beatsin8(5, 0, myMatrix->getNumCols() - 1, 0, 170);
    uint8_t sinBeat4 = beatsin8(5, 0, 255, 0, 0);

    myMatrix->lightOneColumn(sinBeat, CRGB::DarkBlue);
    myMatrix->lightOneColumn(sinBeat2, CRGB::Purple);
    myMatrix->lightOneColumn(sinBeat3, CRGB(0, 200, sinBeat4));

    myMatrix->fadeToBlack(5);

    myMatrix->displayChar(1, 1, 'T', CRGB::Brown);
    myMatrix->displayChar(1, 5, 'E', CRGB::Yellow);
    myMatrix->displayChar(1, 9, 'X', CRGB::White);
    myMatrix->displayChar(1, 13, 'T', CRGB::Red);
}

void text_dynamic_background(LED_Matrix* myMatrix)
{
    uint8_t sinBeat = beatsin8(5, 30, 255, 0, 0);
    uint8_t sinBeat2 = beatsin8(7, 20, 255, 0, 170);

    for (int i = 0; i < myMatrix->getNumRows(); i++)
        myMatrix->lightOneRow(i, CRGB((i * (255 / 2)) / myMatrix->getNumRows(), sinBeat2, sinBeat));

    myMatrix->displayChar(2, 1, 'T', CRGB::Red);
    myMatrix->displayChar(2, 5, 'E', CRGB::Red);
    myMatrix->displayChar(2, 9, 'X', CRGB::Red);
    myMatrix->displayChar(2, 13, 'T', CRGB::Red);
}

void wave_dynamic_background(LED_Matrix* myMatrix)
{
    uint8_t sinBeat_r = beatsin8(1, 0, 255, 0, 0);
    uint8_t sinBeat_g = beatsin8(2, 10, 255, 0, 170);
    uint8_t sinBeat_b = beatsin8(3, 30, 255, 0, 85);
    uint8_t sinBeat_col = beatsin8(15, 0, myMatrix->getNumCols() - 1, 0, 85);
    uint8_t sinBeat_row = beatsin8(10, 0, myMatrix->getNumRows() - 1, 0, 0);

    CRGB color = CRGB(sinBeat_r, sinBeat_g, sinBeat_b);

    for (int i = 0; i < myMatrix->getNumRows(); i++)
        myMatrix->lightOneRow(i, color.addToRGB((i * (255 / 8)) / myMatrix->getNumRows()));

    myMatrix->lightOneColumn(sinBeat_col, CRGB::DarkBlue);
    myMatrix->lightOneRow(sinBeat_row, CRGB::DarkViolet);
    myMatrix->lightOne(sinBeat_row, sinBeat_col, CRGB::Yellow);
}

void dots_dynamic_background(LED_Matrix* myMatrix)
{
    uint8_t sinBeat_r = beatsin8(1, 0, 255, 0, 0);
    uint8_t sinBeat_g = beatsin8(2, 10, 255, 0, 170);
    uint8_t sinBeat_b = beatsin8(3, 30, 255, 0, 85);
    
    uint8_t sinBeat_col_r = beatsin8(1, 0, myMatrix->getNumCols() - 1, 0, 85);
    uint8_t sinBeat_row_r = beatsin8(2, 0, myMatrix->getNumRows() - 1, 0, 0);
    uint8_t sinBeat_col_g = beatsin8(3, 0, myMatrix->getNumCols() - 1, 0, 50);
    uint8_t sinBeat_row_g = beatsin8(2, 0, myMatrix->getNumRows() - 1, 0, 35);
    uint8_t sinBeat_col_b = beatsin8(2, 0, myMatrix->getNumCols() - 1, 0, 5);
    uint8_t sinBeat_row_b = beatsin8(4, 0, myMatrix->getNumRows() - 1, 0, 170);
    uint8_t sinBeat_col_y = beatsin8(3, 0, myMatrix->getNumCols() - 1, 0, 150);
    uint8_t sinBeat_row_y = beatsin8(5, 0, myMatrix->getNumRows() - 1, 0, 1);

    CRGB color = CRGB(sinBeat_r, sinBeat_g, sinBeat_b);

    // for loop through each row of background
    for (int i = 0; i < myMatrix->getNumRows(); i++)
        myMatrix->lightOneRow(i, color.addToRGB((i * (255 / 8)) / myMatrix->getNumRows()));

    myMatrix->lightOne(sinBeat_row_r, sinBeat_col_r, CRGB::Red);
    myMatrix->lightOne(sinBeat_row_g, sinBeat_col_g, CRGB::Green);
    myMatrix->lightOne(sinBeat_row_b, sinBeat_col_b, CRGB::Blue);
    myMatrix->lightOne(sinBeat_row_y, sinBeat_col_y, CRGB::Yellow);
}