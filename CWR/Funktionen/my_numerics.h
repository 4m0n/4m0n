#ifndef MYNUMERICS_H
#define MYNUMERICS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <lapacke.h>
#include <time.h>
//========WICHTIG===========
#define BLACK   "\x1b[30m" // https://gist.github.com/abritinthebay/d80eb99b2726c83feb0d97eab95206c4
#define RED   "\x1B[31m" 
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

#define BRIGHT   "\x1b[1m"
#define DIM   "\x1b[2m"
#define UNDERSCORE   "\x1b[4m"
#define BLINK   "\x1b[5m"
#define REVERSE   "\x1b[7m"
#define HIDDEN   "\x1b[8m"


#define BGblack   "\x1b[40m"
#define BGred   "\x1b[41m"
#define BGgreen   "\x1b[42m"
#define BGyellow   "\x1b[43m"
#define BGblue   "\x1b[44m"
#define BGmagenta   "\x1b[45m"
#define BGcyan   "\x1b[46m"
#define BGwhite   "\x1b[47m"
//=========================
typedef struct{
  double x;
  double y;
}Tuple;
int farbtest(void);
double diff(double x, double delta, double func(double));
double integrate(double left, double right,int N, double integrand(double));
double erf_midpoint(double left, double right,int N, double integrand(double));
double erf_simpson(double left, double right,int N, double integrand(double));
double bisektion(FILE *fp, double a, double b, double t, double stop, double func(double,double));
double newton_raphson(double a, double stop, double func(double));
double diff2(double x, double t, double delta, double func(double,double));
double modulo(double a, double b);
double random_uniform(double a, double b);
Tuple random_gaussian(void);
double mc_integrate(double func(double* ,int), double a[], double b[], int dim, int N);
double mittelpunktsregel(double func(double ,double), double a[], double b[], int dim, double delta, double N[]);
typedef
int ode_func(double, const double[], double[], void*);
void euler_step(double t, double delta_t ,double y[], ode_func func, int dimension, void *params);
void rk2_step(double t, double delta_t, double y[], ode_func func, int dim, void*params);
void rk4_step(double t, double delta_t, double y[], ode_func func, int dim, void*params);
void verlet_step(double t,double delta_t,double y[], ode_func func,int dim, void*params);
int signum(double x);
int printMatrix(int n, int m, double A[n*m],char *label);
double matrixmult(int n, double A[n*n], double B[n*n],double C[n*n]);
int gauss(int n, int m,double A[n*m], int pivoting);
double det(int n, double A[n*n],int pivoting);
void lgs_solve(int n, double A[n*n],double b[n], double x[n],int pivoting);
void inverse(int n, double A[n*n], double A_inverse[n*n]);
double solve_linear_system(lapack_int n);
void lgs_jacobi_solve(int n, double A[], double b[], double x[], int k_max);
#endif
