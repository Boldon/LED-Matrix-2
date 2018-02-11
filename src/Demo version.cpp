#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define Taster 8
#define BRIGHTNESS  80
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 15;

int hue = 0;
int Delay = 50;
int Color = 50;
int Helligkeit = 55;
int Trigger = 0;
int TasterStatus = 0;

uint16_t XY( uint8_t x, uint8_t y){
  uint16_t i;
  	if( y & 0x01) {	uint8_t reverseX = (kMatrixWidth - 1) - x;  i = (y * kMatrixWidth) + reverseX;} 
  	else {	i = (y * kMatrixWidth) + x;	}
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

void Schalter_lesen()
{
TasterStatus = digitalRead(Taster);
if (TasterStatus == 1){	Serial.println("On");	}
else {	Serial.println("Off");	}
}

void loop()
{
	Schalter_lesen();

/*nur für Demo(autoPlay)*/for(int i = 0; i < 2; ++i)  //Außenliniemit Fade ####################################################################
{
  for (int i = 0; i < 14; ++i)/*Ring 0*/ {	Led[i] = Led[224-i] = Led[XY(0,14-i)] = Led[XY(14,i)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 12; ++i)/*Ring 1*/  { Led[16+i] = Led[208-i] =  Led[XY(1,i+1)] = Led[XY(13,12-i+1)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 10; ++i)/*Ring 2*/  { Led[32+i] = Led[192-i] = Led[XY(2,10-i+2)] = Led[XY(12,i+2)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 8; ++i)/*Ring 3*/ {  Led[48+i] = Led[176-i] =  Led[XY(3,i+3)] = Led[XY(11,8-i+3)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 6; ++i)/*Ring 4*/  { Led[64+i] = Led[160-i] =  Led[XY(4,6-i+4)] = Led[XY(10,i+4)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 4; ++i)/*Ring 5*/ { Led[80+i] = Led[144-i] =  Led[XY(5,i+5)] = Led[XY(9,4-i+5)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  for (int i = 0; i < 2; ++i)/*Ring 6*/ { Led[96+i] = Led[128-i] =  Led[XY(6,2-i+6)] = Led[XY(8,i+6)] = CHSV(hue,255,255); FastLED.show(); hue++; FastLED.delay(Delay); }

  Led[112] = CHSV(hue,255,255);/*Middel Dot*/ FastLED.show(); FastLED.delay(200);

  for (int j = 0; j < 135; ++j) /*Middel Dot revese*/  { Led[112].fadeToBlackBy(4); }

  for (int i = 0; i < 2; ++i)/*Ring 6 revese*/  { for (int j = 0; j < 135; ++j)  { Led[96+1-i] = Led[128-1+i] = Led[XY(6,1+i+6)] = Led[XY(8,1-i+6)].fadeToBlackBy(4); }  FastLED.delay(Delay);  }

  for (int i = 0; i < 4; ++i)/*Ring 5 revese*/  { for (int j = 0; j < 135; ++j)  { Led[83-i] = Led[141+i] = Led[XY(5,3-i+5)] = Led[XY(9,1+i+5)].fadeToBlackBy(4); }  FastLED.delay(Delay);  } 

  for (int i = 0; i < 6; ++i)/*Ring 4 revese*/  { for (int j = 0; j < 135; ++j)  { Led[69-i] = Led[155+i] = Led[XY(4,1+i+4)] = Led[XY(10,5-i+4)].fadeToBlackBy(4); } FastLED.delay(Delay); }
 
  for (int i = 0; i < 8; ++i)/*Ring 3 revese*/  { for (int j = 0; j < 135; ++j)  { Led[55-i] = Led[169+i] = Led[XY(3,7-i+3)] = Led[XY(11,1+i+3)].fadeToBlackBy(4); } FastLED.delay(Delay); }

  for (int i = 0; i < 10; ++i)/*Ring 2 revese*/ { for (int j = 0; j < 135; ++j)  { Led[41-i] = Led[183+i] =  Led[XY(2,1+i+2)] = Led[XY(12,9-i+2)].fadeToBlackBy(4); } FastLED.delay(Delay); }

  for (int i = 0; i < 12; ++i)/*Ring 1 revese*/ { for (int j = 0; j < 135; ++j)  { Led[27-i] = Led[197+i] = Led[XY(1,11-i+1)] = Led[XY(13,1+i+1)].fadeToBlackBy(4); } FastLED.delay(Delay); }

  for (int i = 0; i < 14; ++i)/*Ring 0 revese*/ { for (int j = 0; j < 135; ++j)  { Led[13-i] = Led[211+i] = Led[XY(0,1+i)] = Led[XY(14,13-i)].fadeToBlackBy(4); } FastLED.delay(Delay); }

FastLED.clear ();

  /*nur für Demo*/for(int i = 0; i < 2; ++i) // RGBSetDemo####################################################################
  { 
  static uint8_t hue;
  for (int i = 0; i < NUM_LEDS/2; i++) { Led.fadeToBlackBy(20); Led[i] = CHSV(hue++,255,255); Led(NUM_LEDS/2,NUM_LEDS-1) = Led(NUM_LEDS/2 - 1 ,0); FastLED.delay(33); } /*Erste Hälfte der Led´s zur Mitte*/

  for (int i = 0; i < NUM_LEDS/2; i++) { Led.fadeToBlackBy(20); Led[NUM_LEDS/2 - i] = CHSV(hue++,255,255); Led(NUM_LEDS/2,NUM_LEDS-1) = Led(NUM_LEDS/2 - 1 ,0); FastLED.delay(33); } /*Zweite Hälfte der Led´s vom Ende zur Mitte*/
  }

FastLED.clear ();

  /*nur für Demo*/for(int i = 0; i < 200; ++i)  //HexPlus####################################################################
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
FastLED.clear();
//Test 3
  }
}