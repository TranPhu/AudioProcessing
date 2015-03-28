#ifndef _WAVFile_H
#define _WAVFile_H

#include <iostream>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <unistd.h>
#include <fcntl.h>

#include "WAVFormat.h"

using namespace std;

class WAVFile : public WAVFormat{
private:
  string 	fileName;
  int    	idFileName;
  WaveHeader 	*headerFile;
public:
  WAVFile();
  WAVFile(uint32_t _sampleRate, uint16_t _bitDepth, uint16_t _channels,string _fileName) : WAVFormat(_sampleRate, _bitDepth, _channels)
  {
    fileName = _fileName;
  };
  ~WAVFile();
  int 	openFile();
  void 	closeFile();
  char	*readFile();
  int 	writeFile(unsigned char *dataWrite,int sizeDataWrite);
  
};

#endif