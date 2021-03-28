#include <BlinkPin.h>
#include "debug.h"
#include "HexCoord.h"

#define DEBUG 
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
unsigned int sequence[SEQUENCE_LENGTH] = {REFRESH_DELAY * 3};

void initializeBlinkers(){
  for(int i = 0; i < BLINKER_NB; i++){
    blinkers[i] = BlinkPin(pins[i],sequence,SEQUENCE_LENGTH);
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

position currentPos;

void updateBlinkers(){
  float distance = 0.0;
  for( int i = 0; i < BLINKER_NB; i++){
    distance = distanceCart(currentPos, posBlink[i]);
#ifdef DEBUG
    Serial.print("Distance avec l'objet");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(distance);
    Serial.print("; Blinking probability : ");
    Serial.println(gaussian(distance, 0, 5) * 100);
#endif
    blinkers[i].setBlinkProba(gaussian(distance, 0, 5) * 100);
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
  initializePosBlink();
  initializeBlinkers();

  position hexPos;
  hexPos.x = 1;
  hexPos.y = 1;
  currentPos = hexToCart(hexPos);
}



void loop() {
  updateBlinkers();
  blinkers[0].update();

  if (refreshTimer.hasTimedOut())
  {
    #ifdef DEBUG
      Serial.println("[Main] Refresh ! ");
    #endif
    
    
    refreshTimer.reset();
  }
}
