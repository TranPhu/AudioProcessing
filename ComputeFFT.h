#ifndef _COMPUTEFFT_H_
#define _COMPUTEFFT_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define q		10		/* for 2^10 points */
#define N		(1<<q)		/* N-point FFT*/
#define M		(1<<(q+1))	/* M-point IFFT*/
#define spectrum  	0
#define signal     	0
#ifndef PI
#define PI		3.14159265358979323846264338327950288
#endif

typedef float real;
typedef struct{real Re; real Im;} complex;

using namespace std;

class ComputeFFT /*: public OperateComplex*/
{
private:
  int a;
  
public:
  ComputeFFT();
  ~ComputeFFT();
  
  void fft( complex *v, int n, complex *tmp);
  void ifft( complex *v, int n, complex *tmp);
  complex *caculateFFT(float *data,int n);
  float *caculateIFFT(complex *data,int n);
};



/*****************************************/
class OperateComplex
{
private:
  complex C1;
  complex C2;
  
public:
  OperateComplex();
  OperateComplex(complex c1,complex c2);
  ~OperateComplex();
};

#endif