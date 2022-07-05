#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "integrate.h"


double integrate(double left, double right,int N, double integrand(double)){
  double sum = 0;
  double delta_x = (right - left) / N;
  for(int k = 0; k < N; ++k) {
    double x = left + k * delta_x;
    double f = integrand(x);
    //double f = p1(x);
    double A = f * delta_x;
    sum += A;
  }
  return sum;
}
double erf_midpoint(double left, double right,int N, double funktion(double)){
  double y = 0;
  double delta_x = (right - left) / N;
  for (int k = 1; k<N+1; ++k){
    y = y+ funktion(left+k*delta_x + delta_x/2)*delta_x ;
  }
  return y;
}


double erf_simpson(double left, double right,int N, double funktion(double)){
  double y = 0;
  double delta_x = (right - left) / N;
  for (int k = 1; k<N+1; ++k){
    y = y + (delta_x/6)*(funktion(left+k*delta_x)+4.0*funktion(left+k*delta_x+0.5*delta_x)+funktion(left+k*delta_x+delta_x));
    //y = y+ funktion(left+k*delta_x + delta_x/2)*delta_x;
  }
  return y;
}
