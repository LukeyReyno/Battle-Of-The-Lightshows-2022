// adapted from Scott Marley's Video https://youtu.be/4Ut4UK7612M
#include <FastLED.h>

#define NUM_LEDS 128 // two 8 x 8 matrices
#define LED_PIN 27

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(10);
}

// This can be used to verify the order of the RGB colors
void test_order()
{
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  FastLED.show();
}

void iterate_through_all(CRGB::HTMLColorCode color = CRGB::Red, int offset = 0)
{
  int i = offset - 1;
 
  while (i < NUM_LEDS)
  {
    EVERY_N_MILLISECONDS(100)
    {
      leds[i] = CRGB::Black; // turn off
      FastLED.show();
      i++;
      leds[i] = color;
    }
  }
}

void gradient_between(CRGB::HTMLColorCode color1, CRGB::HTMLColorCode color2)
{
  fill_gradient_RGB(leds, NUM_LEDS, color1, color2);
  FastLED.show();
}

void rainbow()
{
  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  FastLED.show();
}

void loop()
{
  EVERY_N_MILLISECONDS(5000)
  {
    gradient_between(CRGB::Magenta, CRGB::Yellow);
  }
  EVERY_N_MILLISECONDS(5000)
  {
    rainbow();
  }
  iterate_through_all(CRGB::Teal);
}
