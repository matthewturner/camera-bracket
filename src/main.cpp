#include "main.h"

void setup()
{
  Serial.begin(9600);

  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  stepper.moveTo(4000);

  // updateListener = new EvtTimeListener(0, true, (EvtAction)update);
  // mgr.addListener(updateListener);

  // endStopListener = new EvtPinListener(END_STOP_PIN, (EvtAction)endStopReached);
  // mgr.addListener(endStopListener);

  Serial.println("Setup complete; looping...");
}

bool endStopReached()
{
  return (digitalRead(END_STOP_PIN) == HIGH);
}

void loop()
{
  if (endStopReached())
  {
    currentBearing = 190;
  }

  if (stepper.distanceToGo() == 0)
  {
    stepper.moveTo(-stepper.currentPosition());
  }
  stepper.run();
}