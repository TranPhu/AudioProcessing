#include "CaptureAudio.h"


CaptureAudio::CaptureAudio()
{
  this->dataCaptured = (unsigned char*)malloc(sizeof(unsigned char*)*BUFFER_SIZE);
  this->dev = RecordAudio::OpenedDevice();
  fflush(stdout);     
  alcCaptureStart(this->dev);
}

CaptureAudio::~CaptureAudio()
{
    delete dataCaptured;
    alcMakeContextCurrent(NULL); 
    alcCaptureCloseDevice(this->dev);
}

int CaptureAudio::captured()
{     
    ALint samplesAvailable; 
    // Get the number of samples available 
    
    alcGetIntegerv(this->dev, ALC_CAPTURE_SAMPLES, 1, &samplesAvailable); 
    
    // Copy the samples to our capture buffer 
    if (samplesAvailable > 0) 
    { 
	alcCaptureSamples(this->dev, this->dataCaptured, samplesAvailable); 
	fflush(stdout); 
	// Advance the buffer (two bytes per sample * number of samples)  
	this->sizeofDataCapture = samplesAvailable * 2; 
    }    
  return sizeofDataCapture;
}

unsigned char* CaptureAudio::returnData()
{
  return this->dataCaptured;
}
