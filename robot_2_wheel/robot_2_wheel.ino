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
  if ((currentMs - prevMs) < CLOCK_CYCLE) return;
  prevMs = currentMs;

  bluefruit_read();

  if (buttons[4]) {  // boost
    lMotor->setSpeed(200);
    rMotor->setSpeed(200);
  } else {
    lMotor->setSpeed(50);
    rMotor->setSpeed(50);
  }

  if (buttons[5]) {  // forward
    lMotor->run(FORWARD);
    rMotor->run(FORWARD);
  } else if (buttons[6]) {  // backward
    lMotor->run(BACKWARD);
    rMotor->run(BACKWARD);
  } else if (buttons[7]) {  // left
    lMotor->run(BACKWARD);
    rMotor->run(FORWARD);
  } else if (buttons[8]) {  // right
    rMotor->run(BACKWARD);
    lMotor->run(FORWARD);
  } else {  // stop
    lMotor->run(RELEASE);
    rMotor->run(RELEASE);
  }
}
