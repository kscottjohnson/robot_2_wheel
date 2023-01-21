#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <bluefruit.h>

// Motor Driver Library
Adafruit_MotorShield driver = Adafruit_MotorShield();

// Motors
Adafruit_DCMotor *lMotor, *rMotor;

// BLE setup
BLEDfu bledfu;
BLEUart bleuart;

// buttons
bool buttons[] = { false, false, false, false, false, false, false, false, false };

#define CLOCK_CYCLE 100
unsigned long currentMs, prevMs;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("hello world!");

  motor_setup();

  bluefruit_setup();

  prevMs = millis();
}

void loop() {
  currentMs = millis();
  if((currentMs - prevMs) < CLOCK_CYCLE) return;
  prevMs = currentMs;

  bluefruit_read();

  //button check
  for (uint8_t b = 1; b <= 8; b++) {
    Serial.print(b);
    if (buttons[b]) {
      Serial.print("  on, ");
    } else {
      Serial.print(" off, ");
    }
  }
  Serial.println();

}
