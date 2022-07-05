#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/my_numerics.h"


typedef struct{
  double plus;
  double minus;
} lsg;

lsg x;

lsg p(double a, double b, double c){
  x.plus = (-b+sqrt(b*b - 4*a*c))/(2*a);
  x.minus = (-b-sqrt(b*b - 4*a*c))/(2*a);
  return  x;
}
lsg p2(double a, double b, double c){
  x.plus = 2*c/(-b-sqrt(b*b-4*a*c));
  x.minus = 2*c/(-b+sqrt(b*b-4*a*c));
  return  x;
}

int main(void){
  //Aufgabe 1
  double a=1;
  double b=-(10e16 + 1)/(10e8);
  double c=1;
  printf("%g\n%g",p(a,b,c).plus,p(a,b,c).minus);

  //Aufgabe 2
  printf("\n\nAufgabe 2 \n\n");
  printf("%g\n%g",p2(a,b,c).plus,p2(a,b,c).minus);
  //
}
