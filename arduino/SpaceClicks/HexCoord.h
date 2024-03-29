#pragma once
#include "Arduino.h" 


typedef struct position{
  float x;
  float y;
} position;

position hexToCart(const position &pos);
position cartToHex(const position &pos);
float distanceCart(const position& cartPos1, const position& cartPos2);

typedef struct polarPosition{
  float r;
  float theta;
} polarPosition;

position polarToCart(polarPosition polarPos, position center);
position polarToCart(polarPosition polarPos);


float gaussian(const float d, const float mean, const float variance);
