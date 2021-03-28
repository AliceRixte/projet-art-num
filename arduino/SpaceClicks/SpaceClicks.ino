#include <BlinkPin.h>
#include "debug.h"

//#define DEBUG 
#ifdef DEBUG
  #define BLINKDEBUG 
#endif

#define REFRESH_DELAY 200



float mult = 4;

SoftTimer refreshTimer;

#define BLINKER_NB 11
int pins[BLINKER_NB];

void initializePinsNano(){
  for( int i = 0; i < BLINKER_NB; i++){
    pins[i] = i + 2;
  }
}

#define SEQUENCE_LENGTH 1
unsigned int sequence[SEQUENCE_LENGTH] = {REFRESH_DELAY * 3};

BlinkPin blinkers[BLINKER_NB];


void updateBlinkers(){
  for( int i = 0; i < BLINKER_NB; i++){
    blinkers[i].update();
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Debug initiated !");
  pinMode(LED_BUILTIN, OUTPUT);
#endif


  randomSeed(analogRead(0));

  refreshTimer.setTimeOutTime(REFRESH_DELAY);
  refreshTimer.reset();

  initializePinsNano();

  for( int i = 0; i < BLINKER_NB; i++){
    BlinkPin tmpBlinker(pins[i],sequence,SEQUENCE_LENGTH);
    blinkers[i]= tmpBlinker;
    
  }
  blinkers[0].begin();
  blinkers[3].begin();
  blinkers[5].begin();
  blinkers[7].begin();
  blinkers[10].begin();
  delay(REFRESH_DELAY);
  blinkers[1].begin();
  blinkers[6].begin();
  blinkers[8].begin();
  delay(REFRESH_DELAY);
  blinkers[2].begin();
  blinkers[4].begin();
  blinkers[9].begin();

}

void loop() {
  updateBlinkers();
  blinkers[0].update();

  if (refreshTimer.hasTimedOut())
  {
   // mult *= 0.99;

    #ifdef DEBUG
      Serial.print("[Main] Refresh ! ");
    #endif
    
   // blinkers[0].setBlinkProba(50);
    //blinkers[4].setBlinkProba(80);
    refreshTimer.reset();
  }
}
