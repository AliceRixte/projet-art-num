#include <BlinkPin.h>
#include "debug.h"

//#define DEBUG 
#ifdef DEBUG
  #define BLINKDEBUG 
#endif

unsigned int delays[1] = {400};

BlinkPin blinker(2,delays,1,50);

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Debug initiated !");
  pinMode(LED_BUILTIN, OUTPUT);
#endif

  randomSeed(analogRead(0));
  blinker.begin();
}

void loop() {
  blinker.update();
}
