#include "ComputeFFT.h"

void ComputeFFT::fft(complex* v, int n, complex* tmp)
{
    if(n>1) 
    {			/* otherwise, do nothing and return */
      int k,m;    
      complex z, w, *vo, *ve;
      
      ve = tmp; vo = tmp+n/2;
      for(k=0; k<n/2; k++) 
      {
	ve[k] = v[2*k];
	vo[k] = v[2*k+1];
      }
      fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
      fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
      
      for(m=0; m<n/2; m++) 
      {
	w.Re = cos(2*PI*m/(double)n);
	w.Im = -sin(2*PI*m/(double)n);
	z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
	z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
	v[  m  ].Re = ve[m].Re + z.Re;
	v[  m  ].Im = ve[m].Im + z.Im;
	v[m+n/2].Re = ve[m].Re - z.Re;
	v[m+n/2].Im = ve[m].Im - z.Im;
      }
    }
    return;
}

void ComputeFFT::ifft(complex* v, int n, complex* tmp)
{
    if(n>1) 
    {			/* otherwise, do nothing and return */
      int k,m;    
      complex z, w, *vo, *ve;
      ve = tmp; vo = tmp+n/2;
      for(k=0; k<n/2; k++)
      {
	ve[k] = v[2*k];
	vo[k] = v[2*k+1];
      }
      ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
      ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
      
      for(m=0; m<n/2; m++)
      {
	w.Re = cos(2*PI*m/(double)n);
	w.Im = sin(2*PI*m/(double)n);
	z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
	z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
	v[  m  ].Re = ve[m].Re + z.Re;
	v[  m  ].Im = ve[m].Im + z.Im;
	v[m+n/2].Re = ve[m].Re - z.Re;
	v[m+n/2].Im = ve[m].Im - z.Im;
      }
    }
    return;
}

complex* ComputeFFT::caculateFFT(float* data, int n)
{
  complex *outputData;
  complex *inputData;
  complex *temp;
  int i;
  
  //
  inputData 	= (complex*)malloc(sizeof(complex*)*n*2);
  outputData	= (complex*)malloc(sizeof(complex*)*n*2);
  temp		= (complex*)malloc(sizeof(complex*)*n*2);
  // load data into Data to inputData
  for(i=0;i<n;i++)
  {
    inputData[i].Im = 0;
    inputData[i].Re = data[i];
  }
  //call caculateFFT funtion
  fft(inputData,n,temp);
  
  for(i=0;i<n;i++)
  {
    outputData[i].Im = inputData[i].Im;
    outputData[i].Re = inputData[i].Re;
  }
  
  free(inputData);
  free(temp);
  return outputData;
}

float* ComputeFFT::caculateIFFT(complex* data, int n)
{
  float *outputData;
  complex *inputData;
  complex *temp;
  int i;
  
  //
  outputData 	= (float*)malloc(sizeof(float*)*n*2);
  inputData	= (complex*)malloc(sizeof(complex*)*n*2);
  temp		= (complex*)malloc(sizeof(complex*)*n*2);
  //
  for(i=0;i<n;i++)
  {
    inputData[i].Re = data[i].Re;
    inputData[i].Im = data[i].Im;
  }
  //call caculateIFFT funtion
  ifft(inputData,n,temp);
  
  for(i=0;i<n;i++)
  {
    outputData[i] = inputData[i].Re/n;
  }
  
  free(inputData);
  free(temp);
  return outputData;
}




/**********************************/
OperateComplex::OperateComplex(complex c1, complex c2)
{
  this->C1 = c1;
  this->C2 = c2;
}

