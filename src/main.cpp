#include "main.h"

Dependency dependency;

void setup()
{
  Serial.begin(9600);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  if (dependency.method())
  {
    Serial.println("Was true");
  }
}