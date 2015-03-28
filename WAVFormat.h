#ifndef _WAV_H_
#define _WAV_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct _WaveHeader{
      char 	RIFF_marker[4];
      uint32_t 	file_size;
      char 	filetype_header[4];
      char 	format_marker[4];
      uint32_t 	data_header_length;
      uint16_t 	format_type;
      uint16_t 	number_of_channels;
      uint32_t 	sample_rate;
      uint32_t 	bytes_per_second;
      uint16_t 	bytes_per_frame;
      uint16_t 	bits_per_sample;
  } WaveHeader;
  
class WAVFormat{
  
public:
  WAVFormat();
  WAVFormat(uint32_t _sampleRate, uint16_t _bitDepth, uint16_t _channels);
  ~WAVFormat();

  WaveHeader* GenericWAVHeader();
  int WriteWAVHeader(int fd, WaveHeader *hdr);
  
private:
 uint32_t sampleRate;
 uint16_t bitDepth;
 uint16_t channels; 
};

#endif