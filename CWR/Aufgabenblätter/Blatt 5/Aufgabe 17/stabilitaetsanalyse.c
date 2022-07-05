#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "../../../Funktionen/my_numerics.h"


double aufgabe1(double n_0, double r_0, double n, double t, double K, double N){
  FILE *fp = fopen("plot.txt","w");
  for (int i = 0; i < N; i++) {
    n = (n_0*exp(r_0*t))/(1+K*n_0*(exp(r_0*t)-1));
    printf("Zeit: %f Menschen: %f\n",t, n );
    fprintf(fp,"%f,%f\n",t,n);
    t+=0.01;
  }
  fclose(fp);
  return 0;
}

double aufgab2( double n_0, double r_0, double n, double t, double K, double N){
  double delta_x=1e-3;
  FILE *fp = fopen("plot.txt","w");

  for (int i = 0; i < N; i++) {
    n = n + delta_x*r_0*n*(1-K*n);
    printf("Zeit: %f Menschen: %f\n",t, n );
    fprintf(fp,"%f,%f\n",t,n);
    t+=delta_x;
  }
  fclose(fp);

  return 0;
}
int main(void){
  double n_0 = 2;
  double r_0 = 10;
  double n;
  double t = 1;
  double K=0;
  double N = 1e2;

  aufgabe1(n_0,r_0,n,t,K,N);
}
