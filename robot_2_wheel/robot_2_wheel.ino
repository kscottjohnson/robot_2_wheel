#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Motor Driver Library
Adafruit_MotorShield driver = Adafruit_MotorShield();

// setup Motors
Adafruit_DCMotor *lMotor = driver.getMotor(1);
Adafruit_DCMotor *rMotor = driver.getMotor(2);

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!driver.begin()) {
    Serial.println("Could not find Motor Shield.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  
  lMotor->setSpeed(0);
  rMotor->setSpeed(0);
}

void loop() {
  uint8_t i;

  Serial.println("forward");
  lMotor->run(FORWARD);
  rMotor->run(FORWARD);
  
  for (i=0; i<255; i++) {
    lMotor->setSpeed(i);
    rMotor->setSpeed(i);
    delay(10);

  }
  for (i=255; i!=0; i--) {
    lMotor->setSpeed(i);
    rMotor->setSpeed(i);
    delay(10);
  }

  Serial.println("backward");
  lMotor->run(BACKWARD);
  rMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    lMotor->setSpeed(i);
    rMotor->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    lMotor->setSpeed(i);
    rMotor->setSpeed(i);
    delay(10);
  }

  Serial.println("end");
  lMotor->run(RELEASE);
  rMotor->run(RELEASE);
  delay(1000);

}
