#ifndef _WORLD_DETECTION_
#define _WORLD_DETECTION_

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "config"

using namespace std;

class WorldDetection
{
private:
  float IMX;
  float IMN;
  float I1 = 0.03*( IMX – IMN ) + IMN;
  float I2 = 4* IMX;
  float ITL = MIN( I1, I2 );
  float ITU = 5* ITL;
  
public:
  /*construct and disconstruct funtions*/
  WorldDetection();
//   WorldDetection(unsigned char* frame);
  ~WorldDetection();
  
  
};


#endif