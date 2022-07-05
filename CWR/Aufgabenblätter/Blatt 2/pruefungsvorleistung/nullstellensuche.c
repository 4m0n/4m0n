#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../../Funktionen/my_numerics.h"


double p1(double x, double t){
  return x- tanh(x/t);
}

int main(void){
  double a = -1; //Anfangswert
  double b = 2; //Endwert
  double t = 0.5; //Funktionsparameter
  double stop = 0.000000001;
  printf("\n\nAufgabe 1 und 2\n\n");
  //Aufgabe 1 und 2
  printf("Bisektion Nullstelle 1: %f\n",bisektion(NULL, a, b, t, stop, p1));
  printf("Newton Raphson Nullstelle 1: %f\n\n",newton_raphson(NULL, b, t, stop, p1));

  a = -0.5; //Anfangswert
  b = 0.1; //Endwert
  printf("Bisektion Nullstelle 2: %f\n",bisektion(NULL, a, b, t, stop, p1));
  printf("Newton Raphson Nullstelle 2: %f\n\n",newton_raphson(NULL, b, t, stop, p1));
  a = 0.9; //Anfangswert
  b = 1; //Endwert
  printf("Bisektion Nullstelle 3: %f\n",bisektion(NULL, a, b, t, stop, p1));
  printf("Newton Raphson Nullstelle 3: %f\n",newton_raphson(NULL, b, t, stop, p1));

  printf("\n\nAufgabe 3\n\n");


  a = -1;
  b = 2;
  //Aufgabe 3
  FILE *fp1 = fopen("plot1.txt","w");
  printf("Daten erstellen für Bisektion: %g\n",bisektion(fp1,a, b, t, stop, p1));
  fclose(fp1);

  FILE *fp2 = fopen("plot2.txt","w");
  printf("Daten erstellen für Newton Raphson: %g\n",newton_raphson(fp2, b, t, stop, p1));
  fclose(fp2);

  //Aufgabe 4

  FILE *fp3 = fopen("plot3.txt","w");
  for (int i = 0; i <= 1200;i++){
    double k = 0.001;
    fprintf(fp3,"%f,%g\n",k*i,newton_raphson(NULL, b, k*i, stop, p1));
  }
  fclose(fp3);

  return 0;
}
