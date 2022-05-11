#include "Music_LED_Matrix_ESPNOW.h"

void Bar_Visualizer(
    LED_Matrix* musicMatrix,
    struct_message data,
    CRGB::HTMLColorCode color, 
    CRGB::HTMLColorCode ceilingColor)
{
    for (int j = 0; j < musicMatrix->getNumCols(); j++)
    {
        if (j == musicMatrix->getNumCols() / 2 || j == (musicMatrix->getNumCols() / 2) + 1)
        {
            musicMatrix->lightOneColumn(j, CRGB::Green, musicMatrix->ratioByMRows(data.monoAverage), false);
            if (data.monoAverage == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else if (j > musicMatrix->getNumCols() / 2)
        {
            musicMatrix->lightOneColumn(j, color, musicMatrix->ratioByMRows(data.channelData[(j - 2) / 2]), false);
            if (data.channelData[(j - 2) / 2] == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
        else
        {
            musicMatrix->lightOneColumn(j, color, musicMatrix->ratioByMRows(data.channelData[j / 2]), false);
            if (data.channelData[j / 2] == musicMatrix->getNumRows())
                musicMatrix->lightOne(0, j, ceilingColor);
        }
    }

    musicMatrix->show();
}
