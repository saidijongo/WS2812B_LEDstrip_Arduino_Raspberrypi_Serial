#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN 8

CRGB leds[NUM_LEDS];

#define GROUP_SIZE 2
#define ANIMATION_DELAY 100

bool isFinished = false;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.setBrightness(100);
  Serial.begin(115200);
  FastLED.clear();
  FastLED.show();
}

void setColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void moveAnimation(CRGB color, int groupSize) {
  for (int i = 0; i <= NUM_LEDS - groupSize; i++) {
    for (int j = 0; j < groupSize; j++) {
      leds[i + j] = color;
    }
    FastLED.show();
    delay(ANIMATION_DELAY);
    for (int j = 0; j < groupSize; j++) {
      leds[i + j] = CRGB::Black;
    }
  }
  // Reverse the animation direction
  for (int i = NUM_LEDS - groupSize; i >= 0; i--) {
    for (int j = 0; j < groupSize; j++) {
      leds[i + j] = color;
    }
    FastLED.show();
    delay(ANIMATION_DELAY);
    for (int j = 0; j < groupSize; j++) {
      leds[i + j] = CRGB::Black;
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read until newline character
    command.trim(); // Remove leading/trailing whitespace

    if (command == "ADIOS") {
      setColor(CRGB(0, 255, 255)); // Ocean blue
      moveAnimation(CRGB::Red, GROUP_SIZE);
      Serial.println("Green light moving on an Ocean blue background");
    } 
    else if (command == "LONGISLAND") {
      setColor(CRGB(139, 69, 19)); // Brownish Yellow
      moveAnimation(CRGB::Red, GROUP_SIZE);
      Serial.println("Long Island Ice Tea LED pattern");
    }
    else if (command == "PEACHCRUSH") {
      setColor(CRGB(0, 255, 0)); // Green
      moveAnimation(CRGB::Red, GROUP_SIZE);
      Serial.println("Peach Crush LED pattern");
    }
    else if (command == "ALLMOTOR") {
      setColor(CRGB::Blue); // Blue background color
      moveAnimation(CRGB::Green, GROUP_SIZE); // Green LEDs
      Serial.println("Moving rainbow effect");
    }
    else if (command == "CUSTOM") {
      setColor(CRGB::Purple); // Purple background color
      moveAnimation(CRGB::Yellow, GROUP_SIZE); // Yellow LEDs
      Serial.println("Custom animation");
    }
    else if (command == "MIDORI") {
      setColor(CRGB::Orange); // Orange background color
      moveAnimation(CRGB::Green, GROUP_SIZE); // Green LEDs
      Serial.println("Midori Sour LED pattern");
    }
    else if (command == "FINISHED") {
      Serial.println("Pump stopped");
      isFinished = true;
    }
    else {
      Serial.println("Invalid command");
    }
  }
  if (!isFinished) {
    setColor(CRGB::Black); // Black background color
    moveAnimation(CRGB::Black, GROUP_SIZE); // Black LEDs
  }
}
