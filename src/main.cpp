// code based on https://gist.github.com/kriegsman/1f7ccbbfa492a73c015e

#include <FastLED.h>

#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  120

#define NUM_LEDS 419
#define DATA_PIN 6

#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 40

CRGBPalette16 currentPalette( CRGB::Black);
CRGBPalette16 targetPalette( PartyColors_p );

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void ChangePalettePeriodically() {
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  
  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    CRGB p = CHSV( HUE_PURPLE, 255, 255);
    CRGB g = CHSV( HUE_GREEN, 255, 255);
    CRGB r = CHSV( HUE_RED, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;
    if( secondHand ==  0)  { targetPalette = RainbowColors_p; }
    // if( secondHand == 10)  { targetPalette = CRGBPalette16( g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
    if( secondHand == 20)  { targetPalette = CRGBPalette16( r,r,r,r, r,w,w,g, g,g,g,g, g,w,w,r); }
    //if( secondHand == 30)  { targetPalette = bhw2_xmas_gp; }
    if( secondHand == 40)  { targetPalette = CloudColors_p; }
    // if( secondHand == 50)  { targetPalette = PartyColors_p; }
  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex + sin8(i*16), brightness);
    colorIndex += 3;
  }
}

//glitter effect
void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;}
}

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

void loop() {

  ChangePalettePeriodically();
  uint8_t maxChanges = 40; //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);

  static uint8_t startIndex = 0;
  startIndex = startIndex - 8; /* motion speed */
  static uint8_t numOfPaletteRepeats = 1;
  static uint8_t paletteBrightness = 180;

  // FillLEDsFromPaletteColors( startIndex);
  fill_palette (leds, NUM_LEDS, startIndex, numOfPaletteRepeats, currentPalette, paletteBrightness, LINEARBLEND);

  addGlitter(30);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}



void testDisplay1() {
  static uint8_t palettePosition = 0;
  while(true) {
    for(uint8_t i=0; i<14; i++) {
      for(int j=levels[i][0]; j<levels[i][1]; j++) {
        // leds[j].setHSV( palettePosition, 255, 255);
        leds[j] = ColorFromPalette(RainbowColors_p, palettePosition, 128, LINEARBLEND);
      }
      palettePosition = palettePosition + (254/14);
      FastLED.show();
      FastLED.delay(100);
    }
    palettePosition = palettePosition - (254/14);
  }
}

