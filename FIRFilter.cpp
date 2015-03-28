#include "FIRFilter.h"


FIRFilter::FIRFilter()
{
}

FIRFilter::~FIRFilter()
{
    delete this->windowFilter;
}

float* FIRFilter::getWindowFilter()
{
    return this->windowFilter;
}

void FIRFilter::setWindowFilter(float* window,int sizeofWindow)
{
    delete this->windowFilter;
    
    this->sizeofWindowFilter = sizeofWindow;
    this->windowFilter = (float*)malloc(sizeof(float*)*sizeofWindow);
    for(int i=0; i<sizeofWindow;i++)
    {
      windowFilter[i] = window[i];
    }
}

float* FIRFilter::conv(float *A, float *B, int lenA, int lenB){
    int size=lenA+lenB-1;
    int i,j,k;
    float tmp;

    float *result = (float*)malloc(sizeof(float)*(size));

    for (i=0;i<size;i++){
        k = i;
        tmp = 0.0;
        for (j=0; j<lenB; j++)
        {
            if(k>=0 && k<lenA)
                tmp += A[k]*B[j];
 
            k = k-1;
            result[i] = tmp;
        }
    }
    return result;
}

float* FIRFilter::getFilter(float *input, float *filter, int lenI, int lenF){
    int a=(int)lenI/20;
    int b=lenI+2*a;
    int c=(int)(lenF-1)/2;
    int i;

    float *tmp = (float*)malloc(sizeof(int)*b);
    for(i=0;i<a;i++){
        tmp[i]=input[0];
    }
    for(;i<lenI+a;i++){
        tmp[i]=input[i-a];
    }
    for(;i<lenI+2*a;i++){
        tmp[i]=input[lenI-1];
    }
    float *value = conv(tmp, filter, b, lenF);
    free(tmp);

    float *result = (float*)malloc(sizeof(float)*(lenI));
    for(i=0;i<lenI;i++){
        result[i] = value[a+c+i];
    }
    free(value);
    
    return result;
}


/*****************************************************/

float WindowFilter::besselI0(float x)
{
   float ax,ans;
   float y;
   if((ax=fabs(x))<3.75){
       y=x/3.75,y=y*y;
       ans=1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492
           +y*(0.2659732+y*(0.360768e-1+y*0.45813e-2)))));
   }
   else
   {
       y=3.75/ax;
       ans=(exp(ax)/sqrt(ax))*(0.39894228+y*(0.1328592e-1
           +y*(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2
           +y*(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1
           +y*0.392377e-2))))))));
   }
   return ans;
}

int WindowFilter::winType(char *wType)
{
  if(strcmp(wType,"rectangular")==0)
    return 1;
  if(strcmp(wType,"bartlett")==0)
    return 2;
  if(strcmp(wType,"hanning")==0)
    return 3;
  if(strcmp(wType,"hamming")==0)
    return 4;
  if(strcmp(wType,"blackman")==0)
    return 5;
  if(strcmp(wType,"kaiser")==0)
    return 6;
  return 0;
}

float WindowFilter::weightEquation(int n,int wType,int order)
{
  float wn;
  float M=(float)order-1;
  float alpha,val1,val2,val3;
  switch(wType)
  {
      case 1://rectangular
        wn = 1;
        break;
      case 2://bartlett
        wn = 1-2*fabs(n-M/2.0)/M;
        break;
      case 3://hanning
        wn = 0.5-0.5*cos(2*M_PI*n/M);
        break;
      case 4://hamming
        wn = 0.54-0.46*cos(2*M_PI*n/M);
        break;
      case 5://blackman
        wn = 0.42-0.5*cos(2*M_PI*n/M)+0.08*cos(4*M_PI*n/M);
        break;
      case 6://kaiser
        alpha = (float)(order-1)/2.0;
        val1 = (float)(n-alpha)/alpha;
        val2 = pow(val1,2);
        val3 = betaKaiser*sqrt(1-val2);
        wn = (float) (besselI0(val3)/besselI0(betaKaiser));
        break;
  }   
  return wn;
}

float WindowFilter::gnLPF(int n,int order,float ft)
{
  float val=(float)(order-1)/2.0;
  if(n==val)
    return 2*ft;
  else
    return sin(2*M_PI*ft*(n-val))/(M_PI*(n-val));
}

float WindowFilter::gnHPF(int n,int order,float ft)
{
  return (float) gnBPF(n,order,ft,0.5);
}

float WindowFilter::gnBPF(int n,int order,float ft1,float ft2)
{
  float val=(float)(order-1)/2.0;
  if(n==val)
    return 2*(ft2-ft1);
  else
    return (sin(2*M_PI*ft2*(n-val))/(M_PI*(n-val)))-(sin(2*M_PI*ft1*(n-val))/(M_PI*(n-val)));
}

float WindowFilter::gnBSF(int n,int order,float ft1,float ft2)
{
  return (float) gnLPF(n,order,ft1)+gnHPF(n,order,ft2);
}

float* WindowFilter::getLPF(char *windowType,int order,float fs,float fc)
{
  float ft=(float)fc/fs;
  int wType = winType(windowType);

  float *result = (float*)malloc(sizeof(float)*order);

  int i;
  for(i=0;i<order;i++){
      result[i]=gnLPF(i,order,ft)*weightEquation(i,wType,order);
  }
  return result;
}

float* WindowFilter::getHPF(char *windowType,int order,float fs,float fc)
{
  float ft=(float)fc/fs;
  int wType = winType(windowType);

  float *result = (float*)malloc(sizeof(float)*order);

  int i;
  for(i=0;i<order;i++){
      result[i]=gnHPF(i,order,ft)*weightEquation(i,wType,order);
  }
  return result;
}

float* WindowFilter::getBPF(char *windowType,int order,float fs,float fc1,float fc2)
{
  float ft1=(float)fc1/fs;
  float ft2=(float)fc2/fs;
  int wType = winType(windowType);

  float *result = (float*)malloc(sizeof(float)*order);

  int i;
  for(i=0;i<order;i++){
      result[i]=gnBPF(i,order,ft1,ft2)*weightEquation(i,wType,order);
  }
  return result;
}

float* WindowFilter::getBSF(char *windowType,int order,float fs,float fc1,float fc2)
{
  float ft1=(float)fc1/fs;
  float ft2=(float)fc2/fs;
  int wType = winType(windowType);

  float *result = (float*)malloc(sizeof(float)*order);

  int i;
  for(i=0;i<order;i++){
      result[i]=gnBSF(i,order,ft1,ft2)*weightEquation(i,wType,order);
  }
  return result;
}

void WindowFilter::writeResponse(char *file,float *arr,int len){
	int i;
	FILE *fo = fopen(file,"wt");
  for(i=0;i<len;i++)
  {
      fprintf(fo,"%e",arr[i]);
      fprintf(fo,"%s","\n");
  }
  fclose(fo);
}