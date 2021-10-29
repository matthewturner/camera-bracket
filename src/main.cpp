#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(LeftEndStopPin, INPUT_PULLUP);
  pinMode(RightEndStopPin, INPUT_PULLUP);

  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  stepper.moveTo(-10000);

  Serial.println("Setup complete; looping...");
}

void loop()
{
  if (leftEndStopReached())
  {
    stepper.setCurrentPosition(MinLeftBearing);
  }
  if (rightEndStopReached())
  {
    stepper.setCurrentPosition(MinRightBearing);
  }
  stepper.run();
}

bool leftEndStopReached()
{
  return (digitalRead(LeftEndStopPin) == LOW);
}

bool rightEndStopReached()
{
  return (digitalRead(RightEndStopPin) == LOW);
}