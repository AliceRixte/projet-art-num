#include <BlinkPin.h>
#include "debug.h"

//#define DEBUG 
#ifdef DEBUG
  #define BLINKDEBUG 
#endif

unsigned int delays[2] = {1000,500};

BlinkPin blinker(2,delays,2);

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Debug initiated !");
  pinMode(LED_BUILTIN, OUTPUT);
#endif

  blinker.begin();
}

void loop() {
  blinker.update();
}
