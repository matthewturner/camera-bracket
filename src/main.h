#ifndef main_h
#define main_h

#include <Arduino.h>
#include <AccelStepper.h>
#include "CommandReader.h"

const byte LeftEndStopPin = 5;
const byte RightEndStopPin = 6;
const short MinLeftBearing = 20;
const short MinRightBearing = 340;
const short StepsInOneRevolution = 4060;
const double DegreesInRevolution = 360.0;

const byte IN1 = 8;
const byte IN2 = 9;
const byte IN3 = 10;
const byte IN4 = 11;

AccelStepper stepper(AccelStepper::MotorInterfaceType::HALF4WIRE, IN1, IN3, IN2, IN4);
CommandReader _commandModule(&Serial);

bool leftEndStopReached();
bool rightEndStopReached();
short stepsFrom(short bearing);
short bearingFrom(short steps);

#endif