#ifndef _RECORD_AUDIO_H_
#define _RECORD_AUDIO_H_

#include <iostream>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <sys/time.h>
#include <time.h> 
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "WAVFile.h"

using namespace std;

class RecordAudio : public WAVFile{ 
 
private:
  int 		idDevice;
  ALCdevice 	*dev;
  unsigned char	*data;
  int 		sizeData;
//   ALCdevice	*mainDev; 
//   ALCcontext	*mainContext;     
//   ALuint 	buffer; 
//   ALuint 	source; 
//   ALint 	playState; 
    
public:
  RecordAudio();
  RecordAudio(uint32_t _sampleRate, uint16_t _bitDepth, uint16_t _channels,string _fileName) : WAVFile(_sampleRate,_bitDepth,_channels,_fileName)
  {};
  ~RecordAudio();
  
  ALCdevice 	*OpenedDevice();
  ALubyte 	*CapturedData(ALCdevice *device);
  void 		writeData();
  void 		start();
  void 		stop();
};

#endif