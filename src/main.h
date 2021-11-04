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
const short DefaultStepsInRevolution = 8000;
const double DegreesInRange = 184.0;
const short MaxSpeed = 1000;
const short EmergencyAcceleration = 10000;
const short StandardAcceleration = 1000;

const byte IN1 = 8;
const byte IN2 = 9;
const byte IN3 = 10;
const byte IN4 = 11;

const byte STOPPED = 0;
const byte CALIBRATING_LEFT = 1;
const byte CALIBRATING_RIGHT = 2;
const byte CALIBRATING_CENTER = 3;
const byte MOVING_LEFT = 4;
const byte MOVING_RIGHT = 5;

short _stepsInRange = DefaultStepsInRevolution;
byte _state = STOPPED;
const char *_states[6];
AccelStepper _stepper(AccelStepper::MotorInterfaceType::HALF4WIRE, IN1, IN3, IN2, IN4);
HardwareStreamReader _streamReader(&Serial);
Command _command;
CommandReader _commandReader(&_streamReader);

bool leftEndStopReached();
bool rightEndStopReached();
short stepsFrom(short bearing);
short bearingFrom(short steps);
void setState(byte state);
short adjust(short relative);
short right(short relative);
short left(short relative);

void calibrateRight();
void calibrateLeft();
void calibrateCenter();

byte state();

void moveTo();
void setupStates();
void reportStatus();
void reportValue(const char *name, const char *value, bool includeDelimiter);
void reportValue(const char *name, short value, bool includeDelimiter);

#endif