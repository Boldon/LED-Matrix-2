#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  80
#define UPDATES_PER_SECOND 60
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
int trigger = 0;

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
  Serial.begin(57600);
}

void loop()
{
  if (trigger == 0)
  {
    FastLED.delay(100);
    trigger ++;
    fill_solid(Led,225,CRGB::Red);
    FastLED.show();
    Serial.println(trigger);
  }

  
  for (int i = 0; i < 140; ++i)
  {
   //Led[5].fadeToBlackBy(10); // so oder fadeToBlackBy(Led,NUM_LEDS,AmmountToFadeEachTime); 256=100% 64=25%
   fadeToBlackBy(Led,225,4);
   FastLED.show();
  }
  Led[14] = CRGB::Red;
FastLED.delay(900);
fill_solid(Led,225,CRGB::Blue);
FastLED.show();


}