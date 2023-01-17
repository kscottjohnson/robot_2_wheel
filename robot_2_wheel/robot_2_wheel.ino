#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Motor Driver Library
Adafruit_MotorShield driver = Adafruit_MotorShield();

// setup Motors
Adafruit_DCMotor *m1 = driver.getMotor(1);

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!driver.begin()) {
    Serial.println("Could not find Motor Shield.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  
  m1->setSpeed(0);
}

void loop() {
  uint8_t i;

  Serial.print("forward");
  m1->run(FORWARD);
  for (i=0; i<255; i++) {
    m1->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    m1->setSpeed(i);
    delay(10);
  }

  Serial.print("backward");
  m1->run(BACKWARD);
  for (i=0; i<255; i++) {
    m1->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    m1->setSpeed(i);
    delay(10);
  }

  Serial.print("end");
  m1->run(RELEASE);
  delay(1000);

}
