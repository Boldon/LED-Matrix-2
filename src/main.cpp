#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  80
#define UPDATES_PER_SECOND 60
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 15;

int hue = 0;
int Delay = 100;

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
  for (int i = 0; i < 14; ++i)/*Ring 0*/
   {
     Led[i] =
     Led[224-i] = 
     Led[XY(0,14-i)] =
     Led[XY(14,i)] = CHSV(hue,255,255);
     FastLED.show();
     hue++;
     FastLED.delay(Delay);
   }

  for (int i = 0; i < 12; ++i)//Ring 1
   {
    Led[16+i] =
    Led[208-i] = 
    Led[XY(1,i+1)] =
    Led[XY(13,12-i+1)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  for (int i = 0; i < 10; ++i)//Ring 2
   {
    Led[32+i] =
    Led[192-i] = 
    Led[XY(2,10-i+2)] =
    Led[XY(12,i+2)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  for (int i = 0; i < 8; ++i)//Ring 3
   {
    Led[48+i] =
    Led[176-i] = 
    Led[XY(3,i+3)] =
    Led[XY(11,8-i+3)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  for (int i = 0; i < 6; ++i)//Ring 4
   {
    Led[64+i] =
    Led[160-i] = 
    Led[XY(4,6-i+4)] =
    Led[XY(10,i+4)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  for (int i = 0; i < 4; ++i)//Ring 5
   {
    Led[80+i] =
    Led[144-i] = 
    Led[XY(5,i+5)] =
    Led[XY(9,4-i+5)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  for (int i = 0; i < 2; ++i)//Ring 6
   {
    Led[96+i] =
    Led[128-i] = 
    Led[XY(6,2-i+6)] =
    Led[XY(8,i+6)] = CHSV(hue,255,255);
    FastLED.show();
    hue++;
    FastLED.delay(Delay);
   }

  Led[112] = CHSV(hue,255,255);
  FastLED.show();
  hue++;
  FastLED.delay(Delay);
}