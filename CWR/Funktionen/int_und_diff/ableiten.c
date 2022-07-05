#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ableiten.h"

double diff(double x, double delta, double func(double)){
  return (func(x+delta)-func(x-delta))/(2*delta);
}
