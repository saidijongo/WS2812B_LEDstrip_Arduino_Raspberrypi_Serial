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

void moveAnimation(CRGB bgColor, CRGB fgColor, int groupSize) {
  while (!isFinished) {
    // Left to right animation
    for (int i = 0; i <= NUM_LEDS - groupSize && !isFinished; i++) {
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = fgColor;
      }
      FastLED.show();
      delay(ANIMATION_DELAY);
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = bgColor;
      }
      if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); // Read until newline character
        command.trim(); // Remove leading/trailing whitespace
        if (command == "FINISHED") {
          isFinished = true;
          FastLED.clear(); // Turn off all LEDs
          FastLED.show();
          Serial.println("Pump stopped");
        }
        else {
          Serial.println("Invalid command");
        }
      }
    }

    // Right to left animation
    for (int i = NUM_LEDS - groupSize - 1; i >= 0 && !isFinished; i--) {
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = fgColor;
      }
      FastLED.show();
      delay(ANIMATION_DELAY);
      for (int j = 0; j < groupSize; j++) {
        leds[i + j] = bgColor;
      }
      if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); // Read until newline character
        command.trim(); // Remove leading/trailing whitespace
        if (command == "FINISHED") {
          isFinished = true;
          FastLED.clear(); // Turn off all LEDs
          FastLED.show();
          Serial.println("Pump stopped");
        }
        else {
          Serial.println("Invalid command");
        }
      }
    }
  }
  isFinished = false;
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read until newline character
    command.trim(); // Remove leading/trailing whitespace

    if (command == "ADIOS") {
      setColor(CRGB(0, 255, 255)); // Set the background color (Ocean blue)
      moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE); // Move green LEDs on Ocean blue background
      Serial.println("Green light moving on an Ocean blue background");
    }
    else if (command == "LONGISLAND") {
      setColor(CRGB(139, 69, 19)); // Set the background color (Brownish Yellow)
      moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE); // Move green LEDs on Brownish Yellow background
      Serial.println("Long Island Ice Tea LED pattern");
    }
    else if (command == "PEACHCRUSH") {
      setColor(CRGB(139, 69, 19)); // Set the background color (Brownish Yellow)
      moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE); // Move green LEDs on Green background
      Serial.println("Peach Crush LED pattern");
    }
    else if (command == "MIDORISOUR") {
      setColor(CRGB(255, 140, 0)); // Set the background color (Orange)
      moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE); // Move green LEDs on Green background
      Serial.println("Midori Sour LED pattern");
    }
    else if (command == "ALLMOTORS") {
      // Implement the "ALLMOTORS" pattern here
      Serial.println("Implement the 'ALLMOTORS' pattern");
    }
    else if (command == "PUMPNUMBER") {
      // Implement the "PUMPNUMBER" pattern here
      Serial.println("Implement the 'PUMPNUMBER' pattern");
    }
    else if (command == "FINISHED") {
      isFinished = true;
      FastLED.clear(); // Turn off all LEDs
      FastLED.show();
      Serial.println("Pump stopped");
    }
    else {
      Serial.println("Invalid command");
    }
  }
}
