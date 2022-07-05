#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include "../../../Funktionen/my_numerics.h"


double func3(double *y, int dim){//für Aufgabe 3

  double betrag = 0;
  for (int i = 0; i < dim; i++) {
    betrag = betrag + y[i]*y[i];
  }
  betrag = sqrt(betrag);

  double x_1 = y[0];
  double x_2 = y[1];
  if (betrag <= 1){ //Diese Stelle "ersetzt" die heaviside in der mc_integrate funktion.
    return (x_1*x_1 + 6*x_1*x_2 +x_2*x_2);
  }

  else {
    return 0;
  }
}

double func2(double *y, int dim){//für Aufgabe 2

  double betrag = 0;
  for (int i = 0; i < dim; i++) {
    betrag = betrag + y[i]*y[i];
  }
  betrag = sqrt(betrag);
  if (betrag <= 1){
    return 1;
  }
  else {
    return 0;
  }
}

double func(double x, double y){ //für Aufgabe 1
  return x*x + 6*x*y +y*y;
}


double aufgabe1(void){
  printf("\n======== Aufgabe 1: ========\n");
  int dim = 2;
  double a[dim];
  double b[dim];
  double delta[5];
  delta[0] = 0.1;
  delta[1] = 0.05;
  delta[2] = 0.025;
  delta[3] = 0.0125;
  delta[4] = 0.001; //hier werden noch kleine delta x gewählt für eine bessere Genauigkeit.

  double N[2];
  //grenzen der Box festlegen
  a[0]=-1;
  b[0]=-1;
  a[1]=1;
  b[1]=1;

  FILE * fp = fopen("plot1.txt","w");
  for (int i = 0; i < 5; i++) {
    //Schrittzahl berechnen
    N[0] = (a[1]-a[0])/delta[i]; //x
    N[1] = (b[1]-b[0])/delta[i]; //y
    double mp = mittelpunktsregel(func, a, b, dim, delta[i], N);
    fprintf(fp, "%g,%f\n",delta[i],mp);
    printf("Das Volumen ist: %f   N*N ist: %g Delta_x ist %g\n", mp, N[0]*N[0], delta[i]);
  }
  printf("\n==> make plot1\n");
  fclose(fp);
  return 0;
}
double aufgabe2(void){
  printf("\n======== Aufgabe 2: ========\n");

  int dim = 2;
  double a[dim];
  double b[dim];
  int N = 10e8; //Wert gewählt damit Pi auf 3 Nachkommastellen genau ist.
  //grenzen der Box festlegen
  /*Anders als bei Aufgabe 1. Hier ist a die Untergrenze und b die Obergrenze um mit der mc_integrate funktion zu funktionieren*/
  a[0]=-1;
  a[1]=-1;
  b[0]=1;
  b[1]=1;
  printf("\nVolumen: %f\n",mc_integrate(func2, a, b, dim, N));
  return 0;
}
double aufgabe3(void){
  printf("\n======== Aufgabe 3: ========\n");

  int dim = 2;
  double a[dim];
  double b[dim];
  int count = 4;
  double delta = 0.1;
  double N[2];
/*  for (int i = 0; i < 5; i++) {
    printf("\nDas berechnete Volumen beträgt: %f für %g Wiederholungen bzw ein delta x von: %g  \n",mc_integrate(func3, a, b, dim, (int)N),N,(b[0]-a[0])/N ); //wenn hier func2 eingesetzt wird, kann man gut sehen wie pi rauskommt.
    N = N *10;
  } */
  FILE * fp = fopen("plot2.txt","w");

  for (int i = 0; i < 35; i++) {
    //Schrittzahl berechnen
    a[0]=-1;
    b[0]=-1;
    a[1]=1;
    b[1]=1;
    N[0] = (a[1]-a[0])/delta; //x
    N[1] = (b[1]-b[0])/delta; //y
    //printf("Durchgang: %i\n", i);
    fprintf(fp, "%g,%f",N[0]*N[0],mittelpunktsregel(func, a, b, dim, delta, N));
    for (int k = 0; k < count; k++) {
      a[0]=-1;
      a[1]=-1;
      b[0]=1;
      b[1]=1;
      fprintf(fp, ",%f",mc_integrate(func3, a, b, dim, (int)(N[0]*N[0])),(int)(N[0]*N[0]),(a[1]-a[0])/(int)(N[0]*N[0]));
    }
    delta = delta * 0.85;
    fprintf(fp, "\n");
  }
  fclose(fp);
  printf("\n\nIm Plot (make plot2) ist klar zu sehen, wie sich das Mittelpunktverfahren VIEL schneller an den Wert annähert.\nRot ist das Mittelpunktverfahren, blau das MC Intergrations verfahren.");
  printf("\n\n==> make plot2\n");
  return 0;
  //Das Verfahren nähert sich sehr schnell an. Bei nur 100.000 Durchläufen wird der Wert bereits auf 2 Nachkommastellen genau ermittelt
}

int main(void){

  //Aufgaben einfach der Reihe nach aus den Kommentaren nehmen und ausführen
  printf("\n\n======== Start ========\n\n Die Plot befehle können am Ende (make plot1 und make plot2) ausgeführt werden\n");
  aufgabe1();
  aufgabe2(); //Mit hoher genauigkeit würde pi rauskommen.
  aufgabe3();

  printf("\n\n======== Ende ========\n");

}
