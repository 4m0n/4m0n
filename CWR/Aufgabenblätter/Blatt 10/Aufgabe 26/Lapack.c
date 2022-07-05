#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../../Funktionen/my_numerics.h"
#include <lapacke.h>

int rechnen(int dim){ //unnötig
  lapack_int info,m=dim,lda=m,ldb=1,nrhs=1;

  FILE *fp = fopen("matrices.dat","r");

  double *A = (double *)malloc(m*m*sizeof(double));
  double *b = (double *)malloc(m*sizeof(double));
  lapack_int *ipiv = (lapack_int *)malloc(m*sizeof(lapack_int)) ;
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<m;j++) {
      fscanf(fp, "%lf", &A[i*m+j]);
    }
    //fscanf(fp, "%lf", &b[i]);
    b[i] = A[i];
  }
  //printMatrix(m,1,b,"Davor");
  info =  LAPACKE_dsysv(LAPACK_ROW_MAJOR, 'U', m, nrhs, A, lda, ipiv, b, ldb);
  //printMatrix(m,1,b,"Danach");

  fclose(fp);
  free(A);
  free(b);
  free(ipiv);


}

int main(void){ 
  FILE *fp=fopen("plot.dat","w");
  for (int i = 500; i <= 5000; i=i+500)
  {
    clock_t begin, end;
    begin = clock();
    //rechnen(i); //Zeit für den gesammten Prozess, ist aber auch nur sinnvoll so
    solve_linear_system(i);
    end = clock();
    double cpu_time = (double) (end-begin)/CLOCKS_PER_SEC;
    printf("Dimension m: %i CPU zeit in Sekunden: %f\n",i,cpu_time);
    fprintf(fp,"%i,%f\n",i,cpu_time);
  }
  
  fclose(fp);
  exit(0); //was auch immer das bedeutet
}
