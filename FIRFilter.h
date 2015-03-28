#ifndef _FIR_FILTER_H
#define _FIR_FILTER_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define betaKaiser 4.0   //only kaiser-filter

using namespace std;

class FIRFilter
{
private:
    float* windowFilter;
    int sizeofWindowFilter;
    string windowType;
    int topFCut;
    int dowFCut;
    /*wav format*/
    int sampleRate;
    
    
public:
    FIRFilter();
    FIRFilter(int size);
    ~FIRFilter();
    float* getWindowFilter();
    void setWindowFilter(float* window, int sizeofWindow);
    float* conv(float *A, float *B, int lenA, int lenB);
    float* getFilter(float *input, float *filter, int lenI, int lenF);
  
};

/**************************************************************/

class WindowFilter
{
private:
    
  
public:
    WindowFilter();
    ~WindowFilter();
    
    float besselI0(float x);
    int winType(char *wType);
    float weightEquation(int n,int wType,int order);
    float gnLPF(int n,int order,float ft);
    float gnHPF(int n,int order,float ft);
    float gnBPF(int n,int order,float ft1,float ft2);
    float gnBSF(int n,int order,float ft1,float ft2);
    float* getLPF(char *windowType,int order,float fs,float fc);
    float* getHPF(char *windowType,int order,float fs,float fc);
    float* getBPF(char *windowType,int order,float fs,float fc1,float fc2);
    float* getBSF(char *windowType,int order,float fs,float fc1,float fc2);
    void writeResponse(char *file,float *arr,int len);
  
};

#endif