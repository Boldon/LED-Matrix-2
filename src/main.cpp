#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  60
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 15;

int hue = 0;
int Delay = 50;
int Color = 0;
int Helligkeit = 255;
int Trigger = 0;
int i = 0;//#####################################

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
//CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
//CRGB* const Led( leds_plus_safety_pixel + 1);
CRGBArray<NUM_LEDS> Led;


uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(Led,NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.begin(57600);
}

void loop()
{
  fill_solid(Led,NUM_LEDS,ColorFromPalette(RainbowColors_p,0,i));


  FastLED.show();
  i = ++i;
}