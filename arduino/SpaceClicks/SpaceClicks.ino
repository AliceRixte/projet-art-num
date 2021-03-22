#include <BlinkBase.h>
#include <BlinkPin.h>
#include <BlinkShiftRegister.h>

#include "debug.h"

int interval = 1000;
unsigned long previousTime = millis();

void setup() {
#ifdef DEBUG
  pinMode(LED_BUILTIN, OUTPUT);
#endif
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;

  }
}
