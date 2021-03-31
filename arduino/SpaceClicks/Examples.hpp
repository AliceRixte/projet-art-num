#pragma once

typedef struct SoundEntity
{
    position (*getPosition)(long unsigned int discreteTulme );
    float (*getMult)(long unsigned int discreteTime);
    float diffuseness;
    
} SoundEntity;

position constPos(long unsigned int discreteTime){
  position hexPos;
  hexPos.x = 0.0;
  hexPos.y = 1.0;
  return hexToCart(hexPos);
}

float constMult(long unsigned int discreteTime){
  return 1.0;
}

SoundEntity localizedEntity{ 
  .getPosition = constPos,
  .getMult = constMult,
  .diffuseness = 0.1
};

position circularMove(long unsigned int discreteTime){
  position cartPos;
  cartPos.x = cos(PI * discreteTime / 90);
  cartPos.y = sin(PI * discreteTime / 90);
  return cartPos;
}

float circularMult(long unsigned int discreteTime){

  return 1 + (0.4 * cos(PI * discreteTime / 210));
}

SoundEntity circularEntity{ 
  .getPosition = circularMove,
  .getMult = circularMult,
  .diffuseness = 1.0
};
