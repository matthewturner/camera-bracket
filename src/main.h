#ifndef main_h
#define main_h

#include <Arduino.h>
#include "Dependency.h"

#include <AccelStepper.h>

AccelStepper stepper(8, 9, 10, 11);

#endif