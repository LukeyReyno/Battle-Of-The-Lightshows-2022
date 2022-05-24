#include "Music_LED_Matrix_ESPNOW.h"

const int defaultFadeTime = 1;

// returns number of rows to fill
// audio Data is a percent
int ratioByMRows(int numRows, int audioData)
{
    return (audioData * numRows / 100) + 1;
}

void Bar_Visualizer(
    LED_Matrix* musicMatrix,
    struct_message data,
    CRGB color, 
    CRGB ceilingColor)
{
    for (int j = 0; j < musicMatrix->getNumCols(); j++)
    {
        if (j == musicMatrix->getNumCols() / 2 || j == (musicMatrix->getNumCols() / 2) + 1)
        {
            musicMatrix->lightOneColumn(j, CRGB::Green, ratioByMRows(musicMatrix->getNumRows(), data.monoAverage), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.monoAverage) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else if (j > musicMatrix->getNumCols() / 2)
        {
            musicMatrix->lightOneColumn(j, color, ratioByMRows(musicMatrix->getNumRows(), data.channelData[(j - 2) / 2]), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.channelData[(j - 2) / 2]) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else
        {
            musicMatrix->lightOneColumn(j, color, ratioByMRows(musicMatrix->getNumRows(), data.channelData[j / 2]), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.channelData[j / 2]) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }

        musicMatrix->fadeToBlack(defaultFadeTime);
    }

    musicMatrix->show();
}

void Bar_Visualizer_blue_wave(
    LED_Matrix* musicMatrix,
    struct_message data,
    CRGB color,
    CRGB ceilingColor)
{
    uint8_t sinBeat_r = beatsin8(2, 0, color.r, 0, 0);
    uint8_t sinBeat_g = beatsin8(3, 0, color.g, 0, 85);
    uint8_t sinBeat_b = beatsin8(8, color.b, 255, 0, 170);

    CRGB newColor = CRGB(sinBeat_r, sinBeat_g, sinBeat_b);
    for (int j = 0; j < musicMatrix->getNumCols(); j++)
    {
        if (j == musicMatrix->getNumCols() / 2 || j == (musicMatrix->getNumCols() / 2) + 1)
        {
            musicMatrix->lightOneColumn(j, CRGB::Green, ratioByMRows(musicMatrix->getNumRows(), data.monoAverage), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.monoAverage) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else if (j > musicMatrix->getNumCols() / 2)
        {
            musicMatrix->lightOneColumn(j, newColor, ratioByMRows(musicMatrix->getNumRows(), data.channelData[(j - 2) / 2]), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.channelData[(j - 2) / 2]) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else
        {
            musicMatrix->lightOneColumn(j, newColor, ratioByMRows(musicMatrix->getNumRows(), data.channelData[j / 2]), false);
            if (ratioByMRows(musicMatrix->getNumRows(), data.channelData[j / 2]) == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }

        musicMatrix->fadeToBlack(defaultFadeTime);
    }

    musicMatrix->show();
}

void floating_dots(LED_Matrix* musicMatrix, CRGB dotColor)
{
    uint8_t sinBeat1 = beatsin8(1, 0, musicMatrix->getNumCols() - 1, 0, 85);
    uint8_t sinBeat2 = beatsin8(2, 0, musicMatrix->getNumRows() - 1, 0, 0);
    uint8_t sinBeat3 = beatsin8(3, 0, musicMatrix->getNumCols() - 1, 0, 50);
    uint8_t sinBeat4 = beatsin8(2, 0, musicMatrix->getNumRows() - 1, 0, 35);
    uint8_t sinBeat5 = beatsin8(2, 0, musicMatrix->getNumCols() - 1, 0, 5);
    uint8_t sinBeat6 = beatsin8(4, 0, musicMatrix->getNumRows() - 1, 0, 170);
    uint8_t sinBeat7 = beatsin8(3, 0, musicMatrix->getNumCols() - 1, 0, 150);
    uint8_t sinBeat8 = beatsin8(5, 0, musicMatrix->getNumRows() - 1, 0, 1);

    musicMatrix->lightOne(sinBeat2, sinBeat1, dotColor);
    musicMatrix->lightOne(sinBeat1, sinBeat2, dotColor);
    musicMatrix->lightOne(sinBeat4, sinBeat3, dotColor);
    musicMatrix->lightOne(sinBeat3, sinBeat4, dotColor);
    musicMatrix->lightOne(sinBeat6, sinBeat5, dotColor);
    musicMatrix->lightOne(sinBeat5, sinBeat6, dotColor);
    musicMatrix->lightOne(sinBeat8, sinBeat7, dotColor);
    musicMatrix->lightOne(sinBeat7, sinBeat8, dotColor);
    musicMatrix->show();
}
