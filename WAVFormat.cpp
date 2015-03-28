#include "WAVFormat.h"


WAVFormat::WAVFormat()
{
}

WAVFormat::WAVFormat(uint32_t _sampleRate, uint16_t _bitDepth, uint16_t _channels)
{
  this->sampleRate = _sampleRate;
  this->bitDepth = _bitDepth;
  this->channels = _channels;
}

WAVFormat::~WAVFormat()
{
}

WaveHeader* WAVFormat::GenericWAVHeader()
{
    WaveHeader *hdr;
    hdr = (WaveHeader*)malloc(sizeof(*hdr));
    if (!hdr) return NULL;

    memcpy(&hdr->RIFF_marker, "RIFF", 4);
    memcpy(&hdr->filetype_header, "WAVE", 4);
    memcpy(&hdr->format_marker, "fmt ", 4);
    hdr->data_header_length = 16;
    hdr->format_type = 1;
    hdr->number_of_channels = channels;
    hdr->sample_rate = sampleRate;
    hdr->bytes_per_second = sampleRate * channels * bitDepth / 8;
    hdr->bytes_per_frame = channels * bitDepth / 8;
    hdr->bits_per_sample = bitDepth;

    return hdr;
}

int WAVFormat::WriteWAVHeader(int fd, WaveHeader *hdr){
    if (!hdr)
        return -1;

    write(fd, &hdr->RIFF_marker, 4);
    write(fd, &hdr->file_size, 4);
    write(fd, &hdr->filetype_header, 4);
    write(fd, &hdr->format_marker, 4);
    write(fd, &hdr->data_header_length, 4);
    write(fd, &hdr->format_type, 2);
    write(fd, &hdr->number_of_channels, 2);
    write(fd, &hdr->sample_rate, 4);
    write(fd, &hdr->bytes_per_second, 4);
    write(fd, &hdr->bytes_per_frame, 2);
    write(fd, &hdr->bits_per_sample, 2);
    write(fd, "data", 4);

    uint32_t data_size = hdr->file_size - 36;
    write(fd, &data_size, 4);

    return 0;
}

