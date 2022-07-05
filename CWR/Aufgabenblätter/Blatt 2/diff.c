#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/int_und_diff/ableiten.h"


static double p1(double x){
  return x*x*(x-1);
  //return 2.0/sqrt(M_PI) * exp(-x*x);
}

int main(void){
  double punkt = 1.0;
  double delta = 1.0;
  for (int i=0;i<=100;i++){
    printf("%i %g\n",i,diff(punkt,1e-16),p1));
}

  return 0;
}
