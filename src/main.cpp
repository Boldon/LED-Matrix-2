#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  125
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
int Color = 0;
int Helligkeit = 55;
int Trigger = 0;

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
  delay( 3100 ); // power-up safety delay
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(Led,NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.begin(57600);
}

void loop()
{
  for (int i = 0; i < 7; ++i) {  Led[XY(0,4+i)]  = CHSV(Color,255,Helligkeit);  }
    for (int i = 0; i < 9; ++i) { Led[XY(1,3+i)]  = CHSV(Color,255,Helligkeit);  }
      for (int i = 0; i < 11; ++i)  { Led[XY(2,2+i)]  = CHSV(Color,255,Helligkeit);  }
        for (int i = 0; i < 13; ++i)  { Led[XY(3,1+i)]  = CHSV(Color,255,Helligkeit);  }

          for (int i = 0; i < 7; ++i) { for (int j = 0; j < 15; ++j)  { Led[XY(4+i,j)]  = CHSV(Color,255,Helligkeit);  } }

        for (int i = 0; i < 13; ++i)  { Led[XY(11,1+i)]  = CHSV(Color,255,Helligkeit);  }
      for (int i = 0; i < 11; ++i)  { Led[XY(12,2+i)]  = CHSV(Color,255,Helligkeit);  }
    for (int i = 0; i < 9; ++i) { Led[XY(13,3+i)]  = CHSV(Color,255,Helligkeit);  }
  for (int i = 0; i < 7; ++i) {  Led[XY(14,4+i)]  = CHSV(Color,255,Helligkeit);  }
  
  FastLED.show();
  FastLED.delay(10);

  if (Trigger == 0)  { Helligkeit++; }
  if (Trigger == 1)  { Helligkeit--;  }
  if (Helligkeit == 120)  { Trigger = 1;  }
  if (Helligkeit == 80)  { Trigger = 0;  }
  
}