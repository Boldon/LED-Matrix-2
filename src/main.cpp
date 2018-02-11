#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS  80
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 15;

int hue = 0;

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

CRGBArray<NUM_LEDS> Led;
CRGBPalette16 CurrentPalette;


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

DEFINE_GRADIENT_PALETTE( bhw2_47_gp ) {
    0,  78, 43,205,
   22,   1,111,114,
   48, 121,255,125,
   56,  38,191,122,
   79,  46, 93,119,
  112,  78, 43,205,
  135,  78, 43,205,
  165,  46, 93,119,
  193,  38,191,122,
  204, 121,255,125,
  226,   1,111,114,
  255,  78, 43,205};
  // Gradient palette "bhw1_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_07_gp ) {
    0, 232, 65,  1,
  255, 229,227,  1};
  // Gradient palette "bhw1_05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_05_gp ) {
    0,   1,221, 53,
  255,  73,  3,178};



void loop()
{
  CurrentPalette = bhw1_05_gp;
    for(int i = 0; i < 2; ++i) // RGBSetDemo####################################################################
  { 
  static uint8_t hue;
  for(int i = 0; i < NUM_LEDS/2; i++) {   
    // fade everything out
    Led.fadeToBlackBy(20);

    // let's set an led value
    Led[i] = ColorFromPalette(CurrentPalette,hue++);

    // now, let's first 20 Led to the top 20 Led, 
    Led(NUM_LEDS/2,NUM_LEDS-1) = Led(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(3);   
  } 
  for (int i = 0; i < NUM_LEDS/2; i++)
    {
      Led.fadeToBlackBy(20);

      Led[NUM_LEDS/2 - i] = ColorFromPalette(CurrentPalette,hue++);

    Led(NUM_LEDS/2,NUM_LEDS-1) = Led(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(3);
    }  
  }
}