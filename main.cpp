
#include <AL/al.h>    // OpenAL header files
#include <AL/alc.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>

#include "RecordAudio.h"
#include "WAVFormat.h"
#include "WAVFile.h"
#include "CaptureAudio.h"

using namespace std;

int main(int argc, char **argv)
{
  string fileName = "fileRecord.wav";
  int sizeofData;
  //unsigned char* dataCapture;
  
   class CaptureAudio *record = new CaptureAudio(500);
   record->captured();
   
   //RecordAudio::start();

//    sizeofData = record->captured();
//    dataCapture = (unsigned char*)malloc(sizeof(unsigned char*)*sizeofData);
//    
//    dataCapture = record->returnData();
//    
//    for(int i;i<sizeofData;i++)
//     {
// 	printf("data[%i] = %i\n",dataCapture[i]);
//     }
  while(1){
    break;
  }
  
   delete record;
  return 1;
}