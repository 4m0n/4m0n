/*----------------------------------*\
|  CWR 2022                          |
|  Blatt 10                          |
\*----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lapacke.h"



/*-----------------------------------------------------------------------------*/


// Just a simple function to print out a matrix/vector

void print_matrix_rowmajor(char *desc, lapack_int m, lapack_int n, double *mat,
                           lapack_int ldm)	
{
  lapack_int i, j;
  printf( "\n %s\n", desc ); 
  for( i = 0; i < m; i++ ) 
  {
    for( j = 0; j < n; j++ ) 
      printf( " %6.2f", mat[i*ldm+j] );
    printf( "\n" );
  }
}


/*-----------------------------------------------------------------------------*/




int main()
{
  // Variables needed for LAPACK
  // - info: takes the returned value from the LAPACK subroutine
  // - m: number of linear equations  
  // - lda: The leading dimension of the matrix A
  // - ldb: The leading dimension of the array b
  // - nrhs: the number of columns of the right hand side
  lapack_int info,m=10,lda=m,ldb=1,nrhs=1;
  
  FILE *file_A = fopen("A.dat","r");
  FILE *file_b = fopen("b.dat","r");
  double *A = (double *)malloc(m*m*sizeof(double)) ;
  double *b = (double *)malloc(m*sizeof(double)) ;
  
  // ipiv is an array of dimension m that stores what lines where
  // changed during the pivoting procedure
  lapack_int *ipiv = (lapack_int *)malloc(m*sizeof(lapack_int)) ;

  for(int i=0;i<m;i++)
  {
    for(int j=0;j<m;j++) fscanf(file_A, "%lf", &A[i*m+j]);
    fscanf(file_b, "%lf", &b[i]);
  }
   

  print_matrix_rowmajor( "Entry Matrix A: ", m, m, A, m );
  print_matrix_rowmajor( "LHS vector b: ", m, 1, b, 1 );

  // The majority of the arguments here where explained at the beginning 
  // of main(), the only left are the first the second parameters, the former 
  // specify how the input vectors (A and b) are organized. Row major means
  // that we have inserted values in A and b going through the rows, i.e. the
  // first m elements of A are the firts row of the matrix. The second arument
  // 'U' says to LAPACK to store the matrix A in the upper form. In this case 
  // it doesn't change the result.
  info =  LAPACKE_dsysv(LAPACK_ROW_MAJOR, 'U', m, nrhs, A, lda, ipiv, b, ldb);
  
  print_matrix_rowmajor( "Solution: ", m, 1, b, 1 );
  
  fclose(file_A);
  fclose(file_b);
  free(A);
  free(b);
  free(ipiv);
 
  exit( 0 );
  
  // Use what you have learned in this example to solve the exercise 26
}
