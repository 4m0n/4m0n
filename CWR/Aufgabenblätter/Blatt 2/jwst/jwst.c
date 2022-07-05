#include <stdio.h>ichteverteilung in einem Stern (Pr  ̈ufungsvorle
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/int_und_diff/ableiten.h"

const double mu_earth = 3.986e14;
const double mu_sun = 1.327e20;
const double omega = 1.991e-7;
const double radius_orbit_earth = 1.496e11;


double acceleration(double r){
  double a_earth= -mu_earth/(r*r);
  double a_sun= -mu_sun/(pow(radius_orbit_earth+r,2));
  double a_centrifugal= omega*omega*(radius_orbit_earth+r);
  printf("Abstand: %g\nErde %g\nSonne %g\nZentrifugalkraft %g\n",r, a_earth, a_sun,a_centrifugal);
  return a_earth + a_sun +a_centrifugal;



}

int main(void){
  for (int i;i<=10;i++){
    printf("%f\n",acceleration(i*1000000));
}
  return 0;
}
