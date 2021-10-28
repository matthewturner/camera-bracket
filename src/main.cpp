#include "main.h"
#include <Stepper.h>

// Define Constants

const int STEPS_PER_REV = 32;
const int GEAR_RED = 64;
const int GEAR_RED2 = 2;

// Number of steps per geared output rotation
const int STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED * GEAR_RED2;

Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

void setup()
{
}

void loop()
{
  steppermotor.setSpeed(1000);
  steppermotor.step(STEPS_PER_OUT_REV);
  delay(1000);

  steppermotor.setSpeed(1000);
  steppermotor.step(-STEPS_PER_OUT_REV);
  delay(1000);
}