#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  80
#define UPDATES_PER_SECOND 60
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 15;

uint16_t XY( uint8_t x, uint8_t y)//reverse odd rows
{
  uint16_t i;  

    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  
  return i;
}
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const Led( leds_plus_safety_pixel + 1);

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(Led,NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop()
{
for (int i = 0; i < NUM_LEDS/2; ++i)
{
  Led[NUM_LEDS/2] = 
  Led[NUM_LEDS/2 +i +1] = 
  Led[NUM_LEDS/2 -i -1] = CRGB::White;
  FastLED.show();
  //Led.fadeToBlackBy(20);
}

FastLED.delay(100);
}