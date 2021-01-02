// code based on https://gist.github.com/kriegsman/1f7ccbbfa492a73c015e

#include <FastLED.h>

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 120

#define NUM_LEDS 419
#define DATA_PIN 23

#define LED_TYPE WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette(CRGB::Black);
CRGBPalette16 targetPalette(PartyColors_p);

uint8_t currentPaletteIndex = 0;

CRGBPalette16 palettes[] = {
    Rainbow_gp,
    CRGBPalette16(
        CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
        CRGB::Red, CRGB::White, CRGB::White, CRGB::Green,
        CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green,
        CRGB::Green, CRGB::White, CRGB::White, CRGB::Red),
    CloudColors_p,
};

TBlendType currentBlendType = LINEARBLEND;

void setup()
{
  delay(1000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if (lastSecond != secondHand)
  {
    lastSecond = secondHand;
    if (secondHand == 20 || secondHand == 40)
    {
      currentPaletteIndex++;
      if (currentPaletteIndex > 3)
      {
        currentPaletteIndex = 0;
      }
      targetPalette = palettes[currentPaletteIndex];
      currentBlendType = LINEARBLEND;
    }
  }
}

//glitter effect
void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void loop()
{
  ChangePalettePeriodically();
  uint8_t maxChanges = 40; //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);

  static uint8_t startIndex = 0;
  startIndex = startIndex - 2; /* motion speed */
  static uint8_t numOfPaletteRepeats = 1;
  static uint8_t paletteBrightness = 100;

  fill_palette(leds, NUM_LEDS, startIndex, numOfPaletteRepeats, currentPalette, paletteBrightness, currentBlendType);

  addGlitter(60);

  FastLED.show();
  // FastLED.delay(5);
}
