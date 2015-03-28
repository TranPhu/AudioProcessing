#include "RecordAudio.h"


RecordAudio::RecordAudio()
{
}

RecordAudio::~RecordAudio()
{
  printf("\nClose Devices\n");
//   alDeleteSources(1, &source); 
//   alDeleteBuffers(1, &buffer); 
//   alcMakeContextCurrent(NULL); 
//   alcCloseDevice(mainDev); 
//   alcCaptureCloseDevice(this->dev);
}

ALCdevice* RecordAudio::OpenedDevice()
{
  ALCdevice *dev;
  const ALCchar	*devices;/*
  
  printf("Available capture devices:\n"); 
  devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER); 

  //while (ptr[0] != NULL)
  while (*devices)
  { 
    printf("   %s\n", devices); 
    devices += strlen(devices) + 1; 
  }

  // Open the default device 
  printf("Opening capture device:\n"); */
  dev = alcCaptureOpenDevice(NULL, 12000, AL_FORMAT_MONO16, 800); /*
  if (dev == NULL) 
  {  
    printf("   Unable to open device!\n"); 
  } 
  devices = alcGetString(dev, ALC_CAPTURE_DEVICE_SPECIFIER); 
  printf("   opened device %s\n", devices); 
  */
  
  return dev;
}

ALubyte* RecordAudio::CapturedData(ALCdevice *device)
{
//   ALubyte 	*captureBufPtr;
//   ALubyte 	captureBuffer[1048576]; 
//   ALint 	samplesAvailable; 
//   ALint 	samplesCaptured;  
//   time_t 	currentTime; 
//   time_t 	lastTime;
//   
//   printf("Starting capture ....!\n"); 
//   fflush(stdout); 
//   /*************************************************
//   // Wait for three seconds to prompt the user 
//   for (int i = 3; i > 0; i--) 
//   { 
//     printf("Starting capture in %i...\r", i); 
//     fflush(stdout); 
//     
//     while (currentTime == lastTime) 
//     { 
//       currentTime = time(NULL); 
//       usleep(10000); 
//     } 
//   } 
//   *************************************/
//   // Capture (roughly) five seconds of audio 
//     lastTime = time(NULL); 
//     currentTime = lastTime; 
//     
//   alcCaptureStart(device); 
//   samplesCaptured = 0; 
//   captureBufPtr = captureBuffer; 
//   while (currentTime < (lastTime + 5)) 
//   { 
//     // Get the number of samples available 
//     alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, 1, &samplesAvailable); 
// 
//     // Copy the samples to our capture buffer 
//     if (samplesAvailable > 0) 
//     { 
//       alcCaptureSamples(device, captureBufPtr, samplesAvailable); 
//       samplesCaptured += samplesAvailable; 
//       printf("Captured %d samples (adding %d)\r", samplesCaptured, 
// 	  samplesAvailable); 
//       fflush(stdout); 
// 
//       // Advance the buffer (two bytes per sample * number of samples) 
//       
//       captureBufPtr += samplesAvailable * 2; 
//     } 
//     // Wait for a bit 
//     usleep(1000); 
// 
//     // Update the clock 
//     currentTime = time(NULL); 
//   } 
//   this->sizeData = samplesCaptured*2;
//   return (ALubyte*)captureBuffer;
}

void RecordAudio::writeData()
{
  WAVFile::writeFile(this->data,sizeData);/*
  for(int i=0;i<sizeData;i++)
  {
    std::cout<<"data "<<i<<": "<<(int)data[i]<<endl;
  }*/
}

void RecordAudio::start()
{
  //WAVFile(sampleRate,bitDepth,channels,fileName);
  WAVFile::openFile();
  this->dev = OpenedDevice();
  this->data = CapturedData(this->dev);
}

void RecordAudio::stop()
{
  WAVFile::closeFile();
  alcMakeContextCurrent(NULL); 
  alcCaptureCloseDevice(this->dev);
}

