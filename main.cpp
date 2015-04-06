
#include <AL/al.h>    // OpenAL header files
#include <AL/alc.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>

#include "config"
#include "RecordAudio.h"
#include "WAVFormat.h"
#include "WAVFile.h"
#include "CaptureAudio.h"

using namespace std;

int main(int argc, char **argv)
{
//   string fileName = "fileRecord.wav";
  int sizeofData;
  unsigned char* dataCapture;
  dataCapture = (unsigned char*)malloc(sizeof(unsigned char*)*BUFFER_SIZE); 
  
  class CaptureAudio *record = new CaptureAudio();     
   
  while(true)
  {
    sizeofData = record->captured();
    dataCapture = record->returnData();
    
    printf("Data captured is size: %i\r",sizeofData);
    usleep(500000);
  }
  
  delete dataCapture;
  delete record;
  return 0;
}