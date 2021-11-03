#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(LeftEndStopPin, INPUT_PULLUP);
  pinMode(RightEndStopPin, INPUT_PULLUP);

  _stepper.setMaxSpeed(MaxSpeed);
  _stepper.setAcceleration(StandardAcceleration);

  Serial.println("Setup complete");

  if (leftEndStopReached())
  {
    calibrateRight();
  }
  else
  {
    calibrateLeft();
  }
}

void loop()
{
  if (leftEndStopReached())
  {
    _stepper.setAcceleration(EmergencyAcceleration);
    if (state() == CALIBRATING_LEFT)
    {
      Serial.println("Left end stop reached, setting position...");
      calibrateRight();
    }
    else if (state() == MOVING_LEFT)
    {
      Serial.println("Left end stop reached, stopping...");
      setState(STOP);
      _stepper.stop();
    }
    else if (state() == CALIBRATING_CENTER)
    {
      Serial.println("Seriously overshot...");
      setState(STOP);
      _stepper.stop();
    }
  }

  if (rightEndStopReached())
  {
    _stepper.setAcceleration(EmergencyAcceleration);
    if (state() == CALIBRATING_RIGHT)
    {
      Serial.println("Right end stop reached, setting position...");
      calibrateCenter();
    }
    else if (state() == MOVING_RIGHT)
    {
      Serial.println("Right end stop reached, stopping...");
      setState(STOP);
      _stepper.stop();
    }
  }

  if (state() == CALIBRATING_CENTER)
  {
    if (_stepper.distanceToGo() == 0)
    {
      Serial.println("Calibrating center position...");
      _stepper.setCurrentPosition(0);
      _stepper.setAcceleration(StandardAcceleration);
      setState(STOPPED);
    }
  }

  uint8_t command = _commandReader.tryReadCommand();
  switch (command)
  {
  case NONE:
    // nothing
    break;
  case STOP:
    Serial.println("Command: STOP");
    setState(STOPPED);
    _stepper.stop();
    break;
  case CALIBRATE:
    Serial.println("Command: CALIBRATE");
    calibrateLeft();
    break;
  case LEFT_45:
    Serial.println("Command: LEFT 45");
    setState(MOVING_LEFT);
    _stepper.move(stepsFrom(left(45)));
    break;
  case RIGHT_45:
    Serial.println("Command: RIGHT 45");
    setState(MOVING_RIGHT);
    _stepper.move(stepsFrom(right(45)));
    break;
  default:
    Serial.print("Unknown command: ");
    Serial.println(command);
    break;
  }

  _stepper.run();
}

void calibrateCenter()
{
  Serial.println("Calibrating center...");
  short currentPosition = _stepper.currentPosition();
  _stepsInRange = abs(currentPosition);
  Serial.print("Current position: ");
  Serial.println(currentPosition);
  setState(CALIBRATING_CENTER);
  Serial.print("Moving to center position: ");
  short centerPosition = currentPosition / 2;
  Serial.println(centerPosition);
  _stepper.moveTo(centerPosition);
}

void calibrateRight()
{
  Serial.println("Calibrating right...");
  setState(CALIBRATING_RIGHT);
  _stepper.setCurrentPosition(0);
  _stepper.move(right(DefaultStepsInRevolution));
}

void calibrateLeft()
{
  Serial.println("Calibrating left...");
  setState(CALIBRATING_LEFT);
  _stepper.move(left(DefaultStepsInRevolution));
}

short right(short relative)
{
  return -relative;
}

short left(short relative)
{
  return relative;
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