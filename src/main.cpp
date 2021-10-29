#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(LeftEndStopPin, INPUT_PULLUP);
  pinMode(RightEndStopPin, INPUT_PULLUP);

  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(1000);
  stepper.moveTo(-stepsFrom(DegreesInRevolution));

  Serial.println("Setup complete; looping...");
}

void loop()
{
  if (leftEndStopReached())
  {
    stepper.setCurrentPosition(stepsFrom(MinLeftBearing));
  }
  if (rightEndStopReached())
  {
    stepper.setCurrentPosition(stepsFrom(MinRightBearing));
  }
  if (stepper.distanceToGo() == 0)
  {
    stepper.moveTo(-stepper.currentPosition());
  }
  stepper.run();
}

short stepsFrom(short bearing)
{
  return bearing / DegreesInRevolution * StepsInOneRevolution;
}

short bearingFrom(short steps)
{
  return steps * DegreesInRevolution / StepsInOneRevolution;
}

bool leftEndStopReached()
{
  return (digitalRead(LeftEndStopPin) == LOW);
}

bool rightEndStopReached()
{
  return (digitalRead(RightEndStopPin) == LOW);
}