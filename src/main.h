#ifndef main_h
#define main_h

#include <Arduino.h>
#include "Dependency.h"
#include <AccelStepper.h>
#include <Eventually.h>

const byte END_STOP_PIN = 6;

const byte MotorInterfaceType = 8;
const byte IN1 = 8;
const byte IN2 = 9;
const byte IN3 = 10;
const byte IN4 = 11;

AccelStepper stepper(MotorInterfaceType, IN1, IN3, IN2, IN4);

EvtManager mgr;
EvtPinListener *endStopListener;
EvtTimeListener *updateListener;

short currentBearing = 0;

bool endStopReached();
bool update();

#endif