#ifndef main_h
#define main_h

#include <Arduino.h>
#include <AccelStepper.h>
#include "CommandReader.h"
#include "HardwareStreamReader.h"

const byte LeftEndStopPin = 5;
const byte RightEndStopPin = 6;
const short MinLeftBearing = 20;
const short MinRightBearing = 340;
const double DegreesInRevolution = 360.0;
const short DefaultStepsInRevolution = 4060;
const double DegreesInRange = 320.0;

const byte IN1 = 8;
const byte IN2 = 9;
const byte IN3 = 10;
const byte IN4 = 11;

const byte STOPPED = 0;
const byte CALIBRATING_LEFT = 1;
const byte CALIBRATING_RIGHT = 2;
const byte MOVING_LEFT = 3;
const byte MOVING_RIGHT = 4;

short _stepsInRange = DefaultStepsInRevolution;
byte _state = STOPPED;
AccelStepper _stepper(AccelStepper::MotorInterfaceType::HALF4WIRE, IN1, IN3, IN2, IN4);
HardwareStreamReader _streamReader(&Serial);
CommandReader _commandReader(&_streamReader);

bool leftEndStopReached();
bool rightEndStopReached();
short stepsFrom(short bearing);
short bearingFrom(short steps);
void setState(byte state);
byte state();

#endif