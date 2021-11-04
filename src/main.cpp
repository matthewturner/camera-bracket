#include "main.h"

void setup()
{
  Serial.begin(9600);

  setupStates();

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

  if (_stepper.distanceToGo() == 0)
  {
    setState(STOPPED);
  }

  _commandReader.tryReadCommand(&_command);
  switch (_command.Value)
  {
  case Commands::NONE:
    // nothing
    break;
  case Commands::STOP:
    Serial.println("Command: STOP");
    setState(STOPPED);
    _stepper.stop();
    break;
  case Commands::STATUS:
    Serial.println("Command: STATUS");
    reportStatus();
    break;
  case Commands::CALIBRATE:
    Serial.println("Command: CALIBRATE");
    calibrateLeft();
    break;
  case Commands::LEFT:
    Serial.println("Command: LEFT");
    setState(MOVING_LEFT);
    _stepper.move(stepsFrom(left(180)));
    break;
  case Commands::RIGHT:
    Serial.println("Command: RIGHT");
    setState(MOVING_RIGHT);
    _stepper.move(stepsFrom(right(180)));
    break;
  case Commands::MOVE_TO:
    Serial.println("Command: MOVE_TO");
    moveTo();
    break;
  default:
    Serial.print("Unknown command: ");
    Serial.println(_command.Value);
    break;
  }

  _stepper.run();
}

void moveTo()
{
  short currentBearing = bearingFrom(adjust(_stepper.currentPosition()));
  short newBearing = _command.Data;
  if (newBearing == currentBearing)
  {
    Serial.println("Already there");
  }
  else
  {
    if (newBearing > currentBearing)
    {
      setState(MOVING_RIGHT);
    }
    else
    {
      setState(MOVING_LEFT);
    }
    _stepper.moveTo(stepsFrom(adjust(newBearing)));
  }
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

short adjust(short relative)
{
  return -relative;
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

void reportStatus()
{
  Serial.println("{");
  reportValue("status", _states[_state], true);
  reportValue("bearing", bearingFrom(adjust(_stepper.currentPosition())), true);
  reportValue("target", bearingFrom(adjust(_stepper.targetPosition())), true);
  reportValue("distanceToGo", _stepper.distanceToGo(), false);
  Serial.println();
  Serial.println("}");
}

void setupStates()
{
  _states[STOPPED] = "stopped";
  _states[CALIBRATING_LEFT] = "calibrating-left";
  _states[CALIBRATING_RIGHT] = "calibrating-right";
  _states[CALIBRATING_CENTER] = "calibrating-center";
  _states[MOVING_LEFT] = "moving-left";
  _states[MOVING_RIGHT] = "moving-right";
}

void reportValue(const char *name, const char *value, bool includeDelimiter)
{
  Serial.print("  \"");
  Serial.print(name);
  Serial.print("\": ");
  Serial.print("\"");
  Serial.print(value);
  Serial.print("\"");
  if (includeDelimiter)
  {
    Serial.println(",");
  }
}

void reportValue(const char *name, short value, bool includeDelimiter)
{
  Serial.print("  \"");
  Serial.print(name);
  Serial.print("\": ");
  Serial.print(value);
  if (includeDelimiter)
  {
    Serial.println(",");
  }
}