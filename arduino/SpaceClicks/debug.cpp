#include "Arduino.h" 
#include "debug.h"

void debugBlink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(70);
  digitalWrite(LED_BUILTIN, LOW);
}
