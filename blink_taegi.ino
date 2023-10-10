#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN 8

CRGB leds[NUM_LEDS];

#define GROUP_SIZE 2
#define ANIMATION_DELAY 100
#define GLOBAL_BRIGHTNESS 255
bool isFinished = false;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.setBrightness(100);
  Serial.begin(115200);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Run the color change animation for 30 seconds
  unsigned long startTime = millis();
  while (millis() - startTime < 30000) {
    // Blink between blue and green
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % GROUP_SIZE == 0) {
        //leds[i] = CRGB(0, 0, 255);  // Blue
        leds[i] = CRGB(255, 255, 0);  // yellow-ish
      } else {
        leds[i] = CRGB(0, 255, 0);  // Green
        //leds[i] = CRGB(0, 0, 255);  // Blue
      }
    }
    FastLED.show();
    delay(ANIMATION_DELAY);
    FastLED.clear();
    FastLED.show();
    delay(ANIMATION_DELAY);
  }

  // After 30 seconds, set all LEDs to pale yellow
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 150);  // Pale Yellow
  }
  FastLED.show();

  while (true) {
   //I love kinchi so much that's why I'm here in Korea
  }
}
