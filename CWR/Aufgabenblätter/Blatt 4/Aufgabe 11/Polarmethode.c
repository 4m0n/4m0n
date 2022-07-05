#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <gsl/gsl_histogram.h>
#include <gsl/gsl_rng.h>
#include "../../../Funktionen/my_numerics.h"

double aufgabe1(void){
  double z = 0;
  double max = 0;
  for (int i; i<100000;i++){
    z = z+random_gaussian().x+random_gaussian().y;
    if (fabs(z)>fabs(max)){
      max = z;
    }
  }
  printf("%f\n%f", z/100000,max);
  return 0;
}
double aufgabe2(void){

  double skala[30];
  for (int i; i<29;i++){
    skala[i]=-5.0+i/2.9;
    //printf("%i, %f\n",i ,skala[i]);
  }
  skala[29]=5.0;

  double verteilung[30];
  for (int i = 0; i < 30; i++) {
    verteilung[i]=0.0;
  }
  int wdh = 10e7;
  for (int i; i<wdh;i++){
    Tuple rndm = random_gaussian();
    double rndmx = rndm.x;
    double rndmy = rndm.y;
    int u = 0;
    for (u; u<30;u++){
      if ((1.0/3.0)>fabs(rndmx-skala[u]) && fabs(rndmx-skala[u])>0){
        verteilung[u]= verteilung[u] + 1;
      }
      if ((1.0/3.0)>fabs(rndmy-skala[u]) && fabs(rndmy-skala[u])>0){
        verteilung[u]= verteilung[u] + 1;
      }
    }
    if (i == wdh*0.1){
      printf("10 Prozent\n");
    }
    else if (i == wdh/2){
      printf("50 Prozent\n");
    }
    else if (i == wdh*0.75){
      printf("75 Prozent\n");
    }
  }

  FILE *fp = fopen("plot.txt","w");
  double erwartungswert = 0;
  double stndabweichung = 0;
  for (int i = 0; i < 30; i++) {
    fprintf(fp,"%f, %f\n",skala[i], verteilung[i] );
    erwartungswert =erwartungswert+ verteilung[i]*skala[i];
  }
  erwartungswert = erwartungswert/wdh;
  printf("\nErwartungswert: %f\n", erwartungswert);

  fclose(fp);


  return 0;
}
double aufgabe3(void){


}

int main(void){
  //aufgabe1();
  //aufgabe2();
  aufgabe3();
}
