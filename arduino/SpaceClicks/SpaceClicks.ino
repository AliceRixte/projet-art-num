#include <BlinkPin.h>
#include "debug.h"
#include "HexCoord.h"
#include "Examples.hpp"

//#define DEBUG 
#ifdef DEBUG
  #define BLINKDEBUG 
#endif

#define REFRESH_DELAY 4
SoftTimer refreshTimer;
long int discreteTime = 0;

#define BLINKER_NB 11
int pins[BLINKER_NB];

void initializePinsNano(){
  for( int i = 0; i < BLINKER_NB; i++){
    pins[i] = i + 2;
  }
  return;
}

position posBlink[BLINKER_NB];
void initializePosBlink(){
  position hexPos;
  hexPos.x = -1, hexPos.y = -1;
  posBlink[0] = hexToCart(hexPos);
  hexPos.x = 0, hexPos.y = -1;
  posBlink[1] = hexToCart(hexPos);
  hexPos.x = 1, hexPos.y = -1;
  posBlink[2] = hexToCart(hexPos);
  hexPos.x = 2, hexPos.y = -1;
  posBlink[3] = hexToCart(hexPos);
  hexPos.x = -1, hexPos.y = 0;
  posBlink[4] = hexToCart(hexPos);
  hexPos.x = 0, hexPos.y = 0;
  posBlink[5] = hexToCart(hexPos);
  hexPos.x = 1, hexPos.y = 0;
  posBlink[6] = hexToCart(hexPos);
  hexPos.x = -2, hexPos.y = 1;
  posBlink[7] = hexToCart(hexPos);
  hexPos.x = -1, hexPos.y = 1;
  posBlink[8] = hexToCart(hexPos);
  hexPos.x = 0, hexPos.y = 1;
  posBlink[9] = hexToCart(hexPos);
  hexPos.x = 1, hexPos.y = 1;
  posBlink[10] = hexToCart(hexPos);
  return;
}

BlinkPin blinkers[BLINKER_NB];
#define SEQUENCE_LENGTH 1
unsigned int sequence[SEQUENCE_LENGTH] = {41};

void initializeBlinkers(){
  for(int i = 0; i < BLINKER_NB; i++){
    blinkers[i] = BlinkPin(pins[i],sequence,SEQUENCE_LENGTH);
  }
  blinkers[0].begin();
  blinkers[3].begin();
  blinkers[5].begin();
  blinkers[7].begin();
  blinkers[10].begin();
  //delay(REFRESH_DELAY);
  blinkers[1].begin();
  blinkers[6].begin();
  blinkers[8].begin();
  //delay(REFRESH_DELAY);
  blinkers[2].begin();
  blinkers[4].begin();
  blinkers[9].begin();
}

#define ENTITY_NB 1
SoundEntity soundEntities[ENTITY_NB] = {circularEntity };

void updateBlinkers(){

  for( int i = 0; i < BLINKER_NB; i++){
    float newProba = 0.0;
    float newMult = 1.0;
    for( int j = 0; j < ENTITY_NB; j++){
      newProba += gaussian(distanceCart(soundEntities[j].getPosition(discreteTime),posBlink[i]),
        0,
        soundEntities[j].diffuseness
      );
      newMult *= soundEntities[j].getMult(discreteTime);
    }
    blinkers[i].setBlinkProba(newProba * 100);
    blinkers[i].setDelayMultiplier(newMult);
    blinkers[i].update();
#ifdef DEBUG
      Serial.print("New proba for");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(newProba * 100);
      Serial.print("; Multiplier factor : ");
      Serial.println(newMult);
#endif

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
  initializePosBlink();
  initializeBlinkers();
  updateBlinkers();

}



void loop() {
  updateBlinkers();

  if (refreshTimer.hasTimedOut())
  {
    #ifdef DEBUG
      Serial.println("[Main] Refresh ! ");
    #endif
    refreshTimer.reset();
    discreteTime++ ;
  }
}
