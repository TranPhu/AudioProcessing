#include "WAVFile.h"

WAVFile::WAVFile()
{  
  this->fileName = "";
}

WAVFile::~WAVFile()
{
  this->closeFile();
}

int WAVFile::openFile()
{
  this->idFileName = open(this->fileName.c_str(), O_WRONLY | O_CREAT, 0644);
  this->headerFile = WAVFormat::GenericWAVHeader();
  WAVFormat::WriteWAVHeader(this->idFileName,this->headerFile);
//   printf("open file: %s\n",this.fileName);
  return idFileName;
}

void WAVFile::closeFile()
{
  //delete headerFile;
  close(idFileName);
}

char* WAVFile::readFile()
{
  char* readedData;
  //add your process
  
  return readedData;  
}

int WAVFile::writeFile(unsigned char* dataWrite, int sizeDataWrite)
{
  int ret;
  
  std::cout<<"idFileName: "<<idFileName<<endl;
  ret =  write(this->idFileName,dataWrite,sizeDataWrite);
  
  return ret;
}


