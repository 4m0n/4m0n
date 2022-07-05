#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../../Funktionen/my_numerics.h"
#include <lapacke.h>

int eins(void){
int dim = 10;
  int k_max = 10;
  lapack_int info,m=dim,lda=m,ldb=1,nrhs=1;
  FILE *fp = fopen("27_matrix.dat","r");
  FILE *fp3 = fopen("27_b.dat","r");
  double *A = (double *)malloc(m*m*sizeof(double));
  double *b = (double *)malloc(m*sizeof(double));
  //double *x = (double *)malloc(m*sizeof(double));
  lapack_int *ipiv = (lapack_int *)malloc(m*sizeof(lapack_int)) ;
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<m;j++) {
      fscanf(fp, "%lf", &A[i*m+j]);
    }
    fscanf(fp3, "%lf", &b[i]);
  }
  double x[10] = {7,3,1,7,1,9,5,3,4,7};
  FILE *fp2=fopen("plot.dat","w");
  //for (int i = 500; i <= 5000; i=i+500)
  for (int i = 10; i <= 5010; i=i+100)
  {
    clock_t begin, end;
    begin = clock();

    lgs_jacobi_solve(dim, A, b, x, i);
    end = clock();
    double cpu_time = (double) (end-begin)/CLOCKS_PER_SEC;
    //printf("Dimension m: %i CPU zeit in Sekunden: %f\n",i,cpu_time);
    fprintf(fp2,"%i,%f\n",i,cpu_time);
  }
  printf("Jacobi solve:\n");
  for (int i = 0; i <dim; i++){
    printf("x: %f, i: %i\n",x[i],i);
  }
  fclose(fp);
  free(A);
  free(b);
  //free(x);
  free(ipiv);
  fclose(fp2);
  return 1;
}

int zwei(void){
  int dim = 10;
  int k_max = 10;
  lapack_int info,m=dim,lda=m,ldb=1,nrhs=1;
  FILE *fp = fopen("27_matrix.dat","r");
  FILE *fp3 = fopen("27_b.dat","r");
  double *A = (double *)malloc(m*m*sizeof(double));
  double *b = (double *)malloc(m*sizeof(double));
  //double *x = (double *)malloc(m*sizeof(double));
  lapack_int *ipiv = (lapack_int *)malloc(m*sizeof(lapack_int)) ;
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<m;j++) {
      fscanf(fp, "%lf", &A[i*m+j]);
    }
    fscanf(fp3, "%lf", &b[i]);
  }
  double x[10] = {7,3,1,7,1,9,5,3,4,7};
  FILE *fp2=fopen("plot.dat","w");
  //for (int i = 500; i <= 5000; i=i+500)
  for (int i = 10; i <= 5010; i=i+100)
  {
    clock_t begin, end;
    begin = clock();
    lgs_gs_solve(dim, A, b, x, i);
    end = clock();
    double cpu_time = (double) (end-begin)/CLOCKS_PER_SEC;
    //printf("Dimension m: %i CPU zeit in Sekunden: %f\n",i,cpu_time);
    fprintf(fp2,"%i,%f\n",i,cpu_time);
  }
  printf("GS solve:\n");
  for (int i = 0; i <dim; i++){
    printf("x: %f, i: %i\n",x[i],i);
  }
  
  fclose(fp);
  free(A);
  free(b);
  //free(x);
  free(ipiv);
  fclose(fp2);
  return 1;
}

int main(void){ 

  eins();
  zwei();
}
