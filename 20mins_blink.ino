#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN 8
#define GROUP_SIZE 2
#define ANIMATION_DELAY 100
#define GLOBAL_BRIGHTNESS 255

CRGB leds[NUM_LEDS];
bool isFinished = false;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
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

void stopAnimation() {
  isFinished = true;
  FastLED.clear();
  FastLED.show();
  Serial.println("Animation stopped");
}

void blinkAnimation() {
  static bool isWhite = true;
  while (!isFinished) {
    if (isWhite) {
      fill_solid(leds, NUM_LEDS, CRGB::White);
    } else {
      fill_solid(leds, NUM_LEDS, CRGB::Green);
    }
    FastLED.show();
    isWhite = !isWhite;
    delay(ANIMATION_DELAY);
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();
      if (command == "FINISHED") {
        stopAnimation();
      } else if (command == "ADIOS") {
        setColor(CRGB(0, 255, 255));
        moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
        Serial.println("ADIOS LED pattern");
      } else if (command == "LONGISLAND") {
        setColor(CRGB(139, 69, 19));
        moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
        Serial.println("Long Island Ice Tea LED pattern");
      } else if (command == "PEACHCRUSH") {
        setColor(CRGB(255, 229, 180));
        moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
        Serial.println("Peach Crush LED pattern");
      } else if (command == "MIDORISOUR") {
        setColor(CRGB(255, 140, 0));
        moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
        Serial.println("Midori Sour LED pattern");
      } else if (command == "ALLMOTORS") {
        setColor(CRGB(148, 0, 211));
        moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
        Serial.println("ALLMOTORS LED pattern");
      } else if (command == "PUMPNUMBER") {
        setColor(CRGB(0, 0, 255));
        moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
        Serial.println("PUMPNUMBER LED pattern");
      } else if (command == "WAITING") {
        waitColor();
        Serial.println(" Wait LED pattern");
      } else if (command == "COMPLETE") {
        complete();
        Serial.println(" Completed, Standby mode");
      } else {
        Serial.println("Invalid command");
      }
    }
  }
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
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command == "FINISHED") {
          stopAnimation();
        } else if (command == "ADIOS") {
          setColor(CRGB(0, 255, 255));
          moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
          Serial.println("ADIOS LED pattern");
        } else if (command == "LONGISLAND") {
          setColor(CRGB(139, 69, 19));
          moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
          Serial.println("Long Island Ice Tea LED pattern");
        } else if (command == "PEACHCRUSH") {
          setColor(CRGB(255, 229, 180));
          moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
          Serial.println("Peach Crush LED pattern");
        } else if (command == "MIDORISOUR") {
          setColor(CRGB(255, 140, 0));
          moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
          Serial.println("Midori Sour LED pattern");
        } else if (command == "ALLMOTORS") {
          setColor(CRGB(148, 0, 211));
          moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
          Serial.println("ALLMOTORS LED pattern");
        } else if (command == "PUMPNUMBER") {
          setColor(CRGB(0, 0, 255));
          moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
          Serial.println("PUMPNUMBER LED pattern");
        } else if (command == "WAITING") {
          waitColor();
          Serial.println(" Wait LED pattern");
        } else if (command == "COMPLETE") {
          complete();
          Serial.println(" Completed, Standby mode");
        } else {
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
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command == "FINISHED") {
          stopAnimation();
        } else if (command == "ADIOS") {
          setColor(CRGB(0, 255, 255));
          moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
          Serial.println("ADIOS LED pattern");
        } else if (command == "LONGISLAND") {
          setColor(CRGB(139, 69, 19));
          moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
          Serial.println("Long Island Ice Tea LED pattern");
        } else if (command == "PEACHCRUSH") {
          setColor(CRGB(255, 229, 180));
          moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
          Serial.println("Peach Crush LED pattern");
        } else if (command == "MIDORISOUR") {
          setColor(CRGB(255, 140, 0));
          moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
          Serial.println("Midori Sour LED pattern");
        } else if (command == "ALLMOTORS") {
          setColor(CRGB(148, 0, 211));
          moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
          Serial.println("ALLMOTORS LED pattern");
        } else if (command == "PUMPNUMBER") {
          setColor(CRGB(0, 0, 255));
          moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
          Serial.println("PUMPNUMBER LED pattern");
        } else if (command == "WAITING") {
          waitColor();
          Serial.println(" Wait LED pattern");
        } else if (command == "COMPLETE") {
          complete();
          Serial.println(" Completed, Standby mode");
        } else {
          Serial.println("Invalid command");
        }
      }
    }
  }
}

void waitColor() {
  CRGB yellow_color(255, 229, 100);
  fill_solid(leds, NUM_LEDS, yellow_color);
  FastLED.show();
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "BLINK") {
      blinkAnimation();
    } else if (command == "ADIOS") {
      setColor(CRGB(0, 255, 255));
      moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
      Serial.println("ADIOS LED pattern");
    } else if (command == "LONGISLAND") {
      setColor(CRGB(139, 69, 19));
      moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
      Serial.println("Long Island Ice Tea LED pattern");
    } else if (command == "PEACHCRUSH") {
      setColor(CRGB(255, 229, 180));
      moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
      Serial.println("Peach Crush LED pattern");
    } else if (command == "MIDORISOUR") {
      setColor(CRGB(255, 140, 0));
      moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
      Serial.println("Midori Sour LED pattern");
    } else if (command == "ALLMOTORS") {
      setColor(CRGB(148, 0, 211));
      moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
      Serial.println("ALLMOTORS LED pattern");
    } else if (command == "PUMPNUMBER") {
      setColor(CRGB(0, 0, 255));
      moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
      Serial.println("PUMPNUMBER LED pattern");
    } else if (command == "COMPLETE") {
      complete();
      Serial.println(" Completed, Standby mode");
    } else if (command == "WAITING") {
      waitColor();
      Serial.println(" Wait LED pattern");
    } else if (command == "FINISHED") {
      stopAnimation();
    } else {
      Serial.println("Invalid command");
    }
  }
}

void complete() {
  unsigned long startTime = millis();
  unsigned long patternStartTime = millis();
  bool patternOn = true;

  // Initial 20 seconds with patterns
  while (millis() - startTime < 20000) {
    // Toggle between patterns every ANIMATION_DELAY milliseconds
    if (millis() - patternStartTime >= ANIMATION_DELAY) {
      patternOn = !patternOn;
      patternStartTime = millis();
    }

    // Set LEDs based on the current pattern
    for (int i = 0; i < NUM_LEDS; i++) {
      if (patternOn) {
        if (i % GROUP_SIZE == 0) {
          leds[i] = CRGB(255, 255, 0);
        } else {
          leds[i] = CRGB(0, 255, 0);
        }
      } else {
        leds[i] = CRGB(70, 70, 70);
      }
    }

    FastLED.show();
  }

  // After the 20-second loop, set LEDs to the final color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 229, 100);
  }
  FastLED.show();

  // Allow checking for new commands after 20 seconds
  while (millis() - startTime < 40000) {
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();
      if (command == "BLINK") {
        blinkAnimation();
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "ADIOS") {
        setColor(CRGB(0, 255, 255));
        moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
        Serial.println("ADIOS LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "LONGISLAND") {
        setColor(CRGB(139, 69, 19));
        moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
        Serial.println("Long Island Ice Tea LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "PEACHCRUSH") {
        setColor(CRGB(255, 229, 180));
        moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
        Serial.println("Peach Crush LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "MIDORISOUR") {
        setColor(CRGB(255, 140, 0));
        moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
        Serial.println("Midori Sour LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "ALLMOTORS") {
        setColor(CRGB(148, 0, 211));
        moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
        Serial.println("ALLMOTORS LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "PUMPNUMBER") {
        setColor(CRGB(0, 0, 255));
        moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
        Serial.println("PUMPNUMBER LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "WAITING") {
        waitColor();
        Serial.println(" Wait LED pattern");
        return;  // Exit the complete function and return to the interrupted animation
      } else if (command == "FINISHED") {
        stopAnimation();
        return;  // Exit the complete function and return to the interrupted animation
      } else {
        Serial.println("Invalid command");
      }
    }
  }
}




void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "BLINK") {
      blinkAnimation();
    } else if (command == "ADIOS") {
      setColor(CRGB(0, 255, 255));
      moveAnimation(CRGB::Red, CRGB(0, 255, 255), GROUP_SIZE);
      Serial.println("ADIOS LED pattern");
    } else if (command == "LONGISLAND") {
      setColor(CRGB(139, 69, 19));
      moveAnimation(CRGB::Red, CRGB(139, 69, 19), GROUP_SIZE);
      Serial.println("Long Island Ice Tea LED pattern");
    } else if (command == "PEACHCRUSH") {
      setColor(CRGB(255, 229, 180));
      moveAnimation(CRGB::Red, CRGB(255, 229, 180), GROUP_SIZE);
      Serial.println("Peach Crush LED pattern");
    } else if (command == "MIDORISOUR") {
      setColor(CRGB(255, 140, 0));
      moveAnimation(CRGB::Red, CRGB(0, 255, 0), GROUP_SIZE);
      Serial.println("Midori Sour LED pattern");
    } else if (command == "ALLMOTORS") {
      setColor(CRGB(148, 0, 211));
      moveAnimation(CRGB::Green, CRGB(148, 0, 211), GROUP_SIZE);
      Serial.println("ALLMOTORS LED pattern");
    } else if (command == "PUMPNUMBER") {
      setColor(CRGB(0, 0, 255));
      moveAnimation(CRGB::Green, CRGB(0, 0, 255), GROUP_SIZE);
      Serial.println("PUMPNUMBER LED pattern");
    } else if (command == "COMPLETE") {
      complete();
      Serial.println(" Completed, Standby mode");
    } else if (command == "WAITING") {
      waitColor();
      Serial.println(" Wait LED pattern");
    } else if (command == "FINISHED") {
      stopAnimation();
    } else {
      Serial.println("Invalid command");
    }
  }
}
