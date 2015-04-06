#ifndef _CAPTURE_AUDIO_H
#define _CAPTURE_AUDIO_H

#include <iostream>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <string.h>
#include <stdlib.h>

#include "config"
#include "WAVFile.h"
#include "RecordAudio.h"


using namespace std;

class CaptureAudio : public RecordAudio
{
private:
  unsigned char* dataCaptured;
  int sizeofDataCapture;
  ALCdevice *dev;
  
public:
  CaptureAudio();
  CaptureAudio(int sizeArray);
  ~CaptureAudio();
  
  int captured();  
  unsigned char* returnData();
};

#endif