#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN 8

CRGB leds[NUM_LEDS];

#define GROUP_SIZE 2
#define ANIMATION_DELAY 100

bool isFinished = false;
bool isAnimationRunning = false;

CRGB currentBackgroundColor = CRGB::Black; // Default background color

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

void moveAnimation(CRGB bgColor, CRGB fgColor, int groupSize) {
  while (!isFinished) {
    currentBackgroundColor = bgColor; // Set the current background color
    isAnimationRunning = true;

    // Left to right animation
    for (int i = 0; i <= NUM_LEDS - groupSize; i++) {
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = fgColor;
      }
      FastLED.show();
      delay(ANIMATION_DELAY);
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = bgColor;
      }
    }

    // Right to left animation
    for (int i = NUM_LEDS - groupSize - 1; i >= 0; i--) {
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = fgColor;
      }
      FastLED.show();
      delay(ANIMATION_DELAY);
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = bgColor;
      }
    }
  }
  isAnimationRunning = false;
}

void stopAnimation() {
  isFinished = true;
  while (isAnimationRunning) {
    // Wait for the current animation to finish
    delay(ANIMATION_DELAY);
  }
  isFinished = false;
  FastLED.clear();
  FastLED.show();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read until newline character
    command.trim(); // Remove leading/trailing whitespace

    stopAnimation(); // Stop any running animation when a new command is received

    if (command == "ADIOS") {
      setColor(currentBackgroundColor); // Set the background color
      moveAnimation(currentBackgroundColor, CRGB(0, 255, 255), GROUP_SIZE); // Ocean blue
      Serial.println("Green light moving on an Ocean blue background");
    }
    else if (command == "LONGISLAND") {
      setColor(currentBackgroundColor); // Set the background color
      moveAnimation(currentBackgroundColor, CRGB(139, 69, 19), GROUP_SIZE); // Brownish Yellow
      Serial.println("Long Island Ice Tea LED pattern");
    }
    else if (command == "PEACHCRUSH") {
      setColor(currentBackgroundColor); // Set the background color
      moveAnimation(currentBackgroundColor, CRGB(0, 255, 0), GROUP_SIZE); // Green
      Serial.println("Peach Crush LED pattern");
    }
    else if (command == "ALLMOTOR") {
      setColor(CRGB::Blue); // Blue background color
      moveAnimation(CRGB::Blue, CRGB::Green, GROUP_SIZE); // Green LEDs
      Serial.println("Moving rainbow effect");
    }
    else if (command == "CUSTOM") {
      setColor(CRGB::Purple); // Purple background color
      moveAnimation(CRGB::Purple, CRGB::Yellow, GROUP_SIZE); // Yellow LEDs
      Serial.println("Custom animation");
    }
    else if (command == "MIDORI") {
      setColor(CRGB::Orange); // Orange background color
      moveAnimation(CRGB::Orange, CRGB::Green, GROUP_SIZE); // Green LEDs
      Serial.println("Midori Sour LED pattern");
    }
    else if (command == "FINISHED") {
      stopAnimation(); // Turn off all LEDs
      Serial.println("Pump stopped");
    }
    else {
      Serial.println("Invalid command");
    }
  }
}
