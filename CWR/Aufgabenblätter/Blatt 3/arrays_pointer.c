#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Funktionen/int_und_diff/virusfunc.h"


malzwei(int *pointer){
  for (int i; i < 100; i++){
    *pointer = (*pointer) *2;
    pointer++;
  }
  return;

}


int main(void){
  int zahlen[100];

  int *pointer = malloc(100 * sizeof(int));


  for (int i; i < 100; i++){
    zahlen[i]=i+10;
    pointer[i] = i +10;
  }
  malzwei(pointer);
  printf("===\n");
  for (int i; i <100; i++){
  //  printf("Array %i --- ", zahlen[i]);
  //  printf("Zeiger %i\n",  *pointer);
    pointer++;
  }

  printf("Aufgabe 5 %i\n", zahlen[11]);
  printf("Aufgabe 5.1 %i\n", 12[zahlen]);

  //free(pointer);
}
