void motor_setup() {
  lMotor = driver.getMotor(1);
  rMotor = driver.getMotor(2);

  if (!driver.begin()) {
    Serial.println("Could not find Motor Shield.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  lMotor->setSpeed(0);
  rMotor->setSpeed(0);
}