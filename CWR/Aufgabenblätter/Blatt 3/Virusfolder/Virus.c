#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../../Funktionen/int_und_diff/virusfunc.h"



int main(void){
  double t = 0;
  double n = 100000;
  double i = 10;
  double mu = 0;

  double alpha = 0.1; //kp
  double beta = 0.1; //stärke ansteckung
  double gamma = 0.01; //heilung
  double omega = 0.1;
  double lambda = 0.1;

  double time = 500;

  double s =n;
  double st=0;
  double e =0;
  double et=0;
  double it=0;
  double r =0;
  double rt=0;
  double mut = 0;
  double smut = 0;
  FILE *fp = fopen("seir.txt","w");

  while (t<= time){
    t++;

    st = -1/n*beta*s*i;
    et = 1/n *beta*s*i - alpha*e;
    it = alpha*e - gamma*i;
    rt = gamma*i;
    mut = -omega * r;
    smut = lambda * mut;

    s = s+st;
    e = e+et;
    i = i+it;
    r=r+rt;

    mu = mu + mut;
    s = s - smut;
    r = r + smut;

    if (i >= n/2){
      beta = 0.01;
    }
    else if ( i < n/3){
      beta = 0.2;
    }
    fprintf(fp, "%f,%f,%f,%f,%f\n",t,s,e,i,r);
  }
  fclose(fp);
}
