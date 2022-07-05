#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "../../../Funktionen/my_numerics.h"

//===== STARTWERTE UND VARIABLEN =====
const int N = 1;
const int dim = N*2;
const double epsilon_0 = 8.85419e-12;
const double epsilon = 1.602e-19;
const double m = 9.109e-31;
const double t_0 = 0;
const double t_f = 2;
const double r_0 = 10;
const double r_f = 10;
const double delta_t = 1e-3;

int coulomb(double t, const double *y, double *f, void*params){
  f[0]=y[1];
  f[1]= (pow(epsilon,2)/(4*M_PI*epsilon_0*y[0]*y[0]))/m;
  return 0;
}

double G(double v_0){
  double y[dim];
  y[0]=r_0;
  y[1]=v_0;
  double t = t_0;
  while (t<t_f){
    verlet_step(t, delta_t, y, coulomb, dim, NULL);
    t += delta_t;
  }
  return fabs(y[0]-r_f);
}

int aufgabe1(void){
  double v_0 = -5;

  v_0 = newton_raphson(v_0, 1e-6, G);
  /* ------- Aufgabe 5 ------- */
  FILE* fp = fopen("plot.dat", "w");
  for(double v = -12.0; v <= 2.0; v += 0.01){
      fprintf(fp, "%f,%f\n", v, G(v));
  }

  fclose(fp);
  short anzahl = 3;
  FILE* fp2[anzahl];
  char filename[64];
  for(int a = 1; a <= anzahl; a++){
      sprintf(filename, "plot2_%d.txt", a);
      fp2[a-1] = fopen(filename, "w");
  }
  for(int a = 0; a < anzahl; a++){
      double y[dim];
      double v[3] = {-12.0, v_0, (-12.0-v_0)/2};
      double t = 0;
      y[0] = r_0;
      y[1] = v[a];
      while(t < t_f){
          verlet_step(t, delta_t, y, coulomb, dim, NULL);
          fprintf(fp2[a], "%f,%f\n", t, y[0]);
          t += delta_t;
      }
      fclose(fp2[a]);
  }
  return 0;
}


int main(void){
  aufgabe1();
  return 0;
}
