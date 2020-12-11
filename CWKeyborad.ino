#include "HID-Project.h"
#include <Adafruit_NeoPixel.h>
// #define BOUNCE_WITH_PROMPT_DETECTION
#include <Bounce2.h>

Bounce dit = Bounce();
Bounce dah = Bounce();

const int ditPin = 0;
const int ditLed = 7;
const int dahPin = 1;
const int dahLed = 8;
const int modePin1 = 2;
const int modePin2 = 3;
const int ledPin = 11;
const int ledCount = 1;

const int paddles = 0;
const int straightKey = 1;
const int keyer = 2;

int mode = paddles;
int debounceInterval = 5;

void setup() {
  Adafruit_NeoPixel pixel(1, 11, NEO_GRBW + NEO_KHZ800);

  pinMode(modePin1, INPUT_PULLUP);
  pinMode(modePin2, INPUT_PULLUP);
  pinMode(ditLed, OUTPUT);
  pinMode(dahLed, OUTPUT);
  
  pixel.begin();
  pixel.setPixelColor(0, pixel.Color(0, 50, 0));

  if (digitalRead(modePin1) == LOW) {
    mode += straightKey;
    pixel.setPixelColor(0, pixel.Color(50, 0, 0));
  }

  if (digitalRead(modePin2) == LOW) {
    mode += keyer;
    debounceInterval = 0;
    pixel.setPixelColor(0, pixel.Color(0, 0, 50));
  }

  pixel.show();

  dit.attach(ditPin, INPUT_PULLUP);
  dah.attach(dahPin, INPUT_PULLUP);

  dit.interval(debounceInterval);
  dah.interval(debounceInterval);

  Keyboard.begin();
}

void loop() {
  dit.update();
  dah.update();

  if (dit.read() == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    digitalWrite(ditLed, HIGH);
  } else {
    Keyboard.release(KEY_LEFT_CTRL);
    digitalWrite(ditLed, LOW);
  }

  if (mode == paddles) {
    if (dah.read() == LOW) {
      Keyboard.press(KEY_RIGHT_CTRL);
      digitalWrite(dahLed, HIGH);
    } else {
      Keyboard.release(KEY_RIGHT_CTRL);
      digitalWrite(dahLed, LOW);
    }
  }
}
