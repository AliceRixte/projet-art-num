#include "HexCoord.h"

position hexToCart(const position& hexPos){
  position cartPos;
  cartPos.x = hexPos.x + 0.5 * hexPos.y;
  cartPos.y = 0.866 * hexPos.y;
  return cartPos;
}

position cartToHex(const position& cartPos){
  position hexPos;
  hexPos.x = cartPos.x - 0.577 * cartPos.y;
  hexPos.y = 1.1547 * cartPos.y;
  return hexPos;
}

float distanceCart(const position& cartPos1, const position& cartPos2){
  return sqrt( sq(cartPos1.x - cartPos2.x) + sq(cartPos1.y - cartPos2.y) );
}

float gaussian(const float d, const float mean, const float variance){
  return exp( (sq(mean) - sq(d - mean)) / (2 * variance) );
}

position polarToCart(polarPosition polarPos, position center){
   position cartPos;
   cartPos.x = cos(polarPos.theta) * polarPos.r + center.x;
   cartPos.y = sin(polarPos.theta) * polarPos.r + center.y;
   return cartPos;
}

position polarToCart(polarPosition polarPos){
   position cartPos;
   cartPos.x = cos(polarPos.theta) * polarPos.r ;
   cartPos.y = sin(polarPos.theta) * polarPos.r ;
   return cartPos;
}
