#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define BRIGHTNESS          128
#define FRAMES_PER_SECOND  120

#define NUM_LEDS 419
#define DATA_PIN 6

#define  CURRENT_LEVEL 13
#define LEVELS 12

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int levels[][2] = {
  {0,75},
  {76, 115},
  {116, 155},
  {156, 185},
  {186, 215},
  {216, 245},
  {246, 275},
  {276, 305},
  {306, 328},
  {329, 353},
  {353, 381},
  {381, 408},
  {408, 419},
  {0, 419},
};

CRGB leds[NUM_LEDS];

void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void setup() {
	delay(3000); // 3 second delay for recovery
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);
  currentPalette = PartyColors_p;
  currentPalette = CloudColors_p;
  currentBlending = LINEARBLEND;

}

static uint8_t hue = 0;

void rainbowSweepUp() {
  while(1) {
    for( uint8_t l =0; l<LEVELS; l++ ) {
      for ( int i=levels[l][0]; i<levels[l][1]; i++) {
        // leds[i] = CHSV(hue, 255, 255);
        leds[i] = ColorFromPalette( currentPalette, hue, 255, currentBlending);
      }
      hue += 1;
    }
    FastLED.show();
    FastLED.delay(1000/FRAMES_PER_SECOND);
    // delay(100);
  }
}

void xmasColors1() {
  uint16_t color = 0x0000FF;
  while(1) {
    if (color == 0x0000FF) color = 0xFF0000;
    if (color == 0xFF0000) color = 0x00FF00;
    if (color == 0x00FF00) color = 0x0000FF;
    for( uint8_t l =0; l<LEVELS; l++ ) {
      for ( int i=levels[l][0]; i<levels[l][1]; i++) {
        leds[i] = color;
      }
    }
    FastLED.show();
    FastLED.delay(1000/FRAMES_PER_SECOND);
    delay(50);
  }
}


void loop() {

  static uint8_t startIndex = 0;
  startIndex = startIndex + 2; /* higher = faster motion */

  fill_palette( leds, NUM_LEDS, 
    startIndex, 1, /* higher = narrower stripes */ 
    currentPalette, 255, LINEARBLEND);

  FastLED.show();
  FastLED.delay(1000 / 60);
  
  // rainbowSweepUp();
  // xmasColors1();
}


