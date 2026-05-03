#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "all_frames.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define TOUCH_PIN 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool animationPlaying = true;

int currentFrame = 0;
int frameDelay = 42;

unsigned long lastFrameTime = 0;

void setup() {

  Serial.begin(115200);

  pinMode(TOUCH_PIN, INPUT);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {

    Serial.println("SSD1306 allocation failed");

    while (1);
  }

  display.clearDisplay();
  display.display();

  Serial.println("OLED Ready");
}

void loop() {

  // -------- TOUCH CONTROL --------

  if (digitalRead(TOUCH_PIN) == HIGH) {

    unsigned long pressStart = millis();

    // Wait until released
    while (digitalRead(TOUCH_PIN) == HIGH) {
      delay(10);
    }

    unsigned long pressTime = millis() - pressStart;

    // LONG PRESS
    if (pressTime > 1000) {

      currentFrame = 0;

      Serial.println("Animation Restarted");
    }

    // SHORT PRESS
    else {

      animationPlaying = !animationPlaying;

      Serial.println(animationPlaying ? "PLAY" : "PAUSE");
    }

    delay(250);
  }

  // -------- ANIMATION --------

  if (animationPlaying &&
      millis() - lastFrameTime >= frameDelay) {

    lastFrameTime = millis();

    display.clearDisplay();

    display.drawBitmap(
      0,
      0,
      frames[currentFrame],
      FRAME_WIDTH,
      FRAME_HEIGHT,
      SSD1306_WHITE
    );

    display.display();

    currentFrame++;

    if (currentFrame >= TOTAL_FRAMES) {
      currentFrame = 0;
    }
  }
}