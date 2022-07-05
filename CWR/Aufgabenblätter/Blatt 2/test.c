#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/int_und_diff/integrate.h"


static double p1(double x){
  return 2.0/sqrt(M_PI) * exp(-pow(x,2.0));
  //return 2.0/sqrt(M_PI) * exp(-x*x);
}

int plot(double left,double right, int N, double p1(double)){
  int i;
  FILE *fp = fopen("plot.txt","w");
  for (i=0;i<=N;i++){
    fprintf(fp,"%d,%g,%g,%g\n",i,integrate(left,right,i,p1), erf_midpoint(left,right,i,p1),erf_simpson(left,right,i,p1));
  }
  printf("Done\n");
  fclose(fp);
}

int main(void){
  double left = 0.0;
  double right = 10.0;
  int N = 50;

  printf("Integralwert Rimann: %f\n", integrate(left,right,N,p1));
  printf("Integralwert Mittelwertfunktion: %f\n", erf_midpoint(left,right,N,p1));
  printf("Integralwert Simpsonfunktion: %f\n", erf_simpson(left,right,N,p1));
  plot(left,right,N, p1);


  return 0;
}
