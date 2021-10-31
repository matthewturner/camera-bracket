#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(LeftEndStopPin, INPUT_PULLUP);
  pinMode(RightEndStopPin, INPUT_PULLUP);

  _stepper.setMaxSpeed(1500);
  _stepper.setAcceleration(1000);

  Serial.println("Setup complete");

  if (!leftEndStopReached())
  {
    Serial.println("Calibrating...");
    setState(CALIBRATING_LEFT);
    _stepper.move(-DefaultStepsInRevolution);
  }
}

void loop()
{
  if (leftEndStopReached())
  {
    _stepper.stop();

    if (state() == CALIBRATING_LEFT)
    {
      _stepper.setCurrentPosition(0);
      setState(CALIBRATING_RIGHT);
      _stepper.move(DefaultStepsInRevolution);
    }
  }

  if (rightEndStopReached())
  {
    _stepper.stop();

    if (state() == CALIBRATING_RIGHT)
    {
      _stepsInRange = _stepper.currentPosition();
      _stepper.setCurrentPosition(_stepsInRange / 2);
      setState(MOVING_LEFT);
      _stepper.moveTo(0);
    }
  }

  uint8_t command = _commandReader.tryReadCommand();
  switch (command)
  {
  case STOP:
    setState(STOPPED);
    _stepper.stop();
    break;
  case CALIBRATE:
    setState(CALIBRATING_LEFT);
    _stepper.move(-DefaultStepsInRevolution);
    break;
  case LEFT_45:
    setState(MOVING_LEFT);
    _stepper.move(stepsFrom(-45));
    break;
  case RIGHT_45:
    setState(MOVING_RIGHT);
    _stepper.move(stepsFrom(45));
    break;
  }
  _stepper.run();
}

byte state()
{
  return _state;
}

void setState(byte state)
{
  _state = state;
}

short stepsFrom(short bearing)
{
  return bearing / DegreesInRange * _stepsInRange;
}

short bearingFrom(short steps)
{
  return steps * DegreesInRange / _stepsInRange;
}

bool leftEndStopReached()
{
  return (digitalRead(LeftEndStopPin) == LOW);
}

bool rightEndStopReached()
{
  return (digitalRead(RightEndStopPin) == LOW);
}