#include <stdio.h>double
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include "../../../Funktionen/my_numerics.h"




double rho_Sn(double *y, int dim)
{
  double betrag = 0;
  for (int i = 0; i < dim; i++) {
    betrag = betrag + y[i]*y[i];
  }
  betrag = sqrt(betrag);
  if (betrag <= 1){ //Vollkugel
    return 1;
  }
  //if (betrag <= 1 && betrag >= 0.9){ //Kugelschale
  //  return 1;
  //}
  else {
    return 0;
  }
}

int main(void){
  FILE * fp = fopen("plot.txt","w");
  for (int k = 1; k < 16; k++) {
    printf("\n\n\n===DURCHGANG  %i ===\n\n\n", k);
    int dim = k;
    double a[dim];
    double b[dim];
    for (int i = 0; i < dim; i++) {
      a[i]=-1;
      b[i]=1;
    }
    int N =10e6;
    double summe =mc_integrate(rho_Sn, a, b, dim, N);
    fprintf(fp, "%i,%f\n",k,summe);
    printf("\nVolumen Hyperkugel %f in %i Dimensionen\n", summe, dim);
  }
  fclose(fp);
  return 0;
}
//Das Array in my_num ist immer sehr klein -> warum speicherplatz frei geben
