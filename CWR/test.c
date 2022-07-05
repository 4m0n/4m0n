#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/int_und_diff/integrate.h"


double p1(double x){
  return 2.0/sqrt(M_PI) * exp(-pow(x,2.0));
  //return 2.0/sqrt(M_PI) * exp(-x*x);
}

double erf_midpoint(double x, double delta_x){
  double y = 0;
  double left = 0.0;
  double right = x;
  double N = (right - left)/delta_x;
  for (int k = 1; k<N+1; ++k){
    y = y+ p1(left+k*delta_x + delta_x/2)*delta_x ;
  }
  return y;
}


double erf_simpson(double x, double delta_x){
  double y = 0;
  double left = 0.0;
  double right = x;
  double N = (right - left)/delta_x;

  for (int k = 1; k<N+1; ++k){
    y = y+ p1(left+k*delta_x + delta_x/2)*delta_x;
  }
  return y;
}


int main(void){
  double left = 0.0;
  double right = 2.0;
  int N = 1000;
  double x = 2; //startwert
  double delta_x = (right - left) / N;

  printf("Integralwert Rimann: %f\n", integrate(left,right,N,p1));
  //printf("Integralwert Mittelwertfunktion: %f\n", rf_midpoint(x,delta_x));
  //printf("Integralwert Simpsonfunktion: %f\n", erf_simpson(x,delta_x));


  return 0;
}
