#include "main.h"

Dependency dependency;

void setup()
{
  Serial.begin(9600);

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  if (stepper.distanceToGo() == 0)
  {
    stepper.moveTo(-stepper.currentPosition());
  }
  stepper.run();
}