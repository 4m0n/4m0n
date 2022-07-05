#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "../../../Funktionen/my_numerics.h"

/* TODO */
/*------------------------  PHYSIKALISCHE KONSTANTEN  -------------------------*/

const int N = 1;              // Anzahl der Pendel
const double k = 100;           // Federhaerte [N/m]
const double base_length = 1; // Basislaenge der Federn [m]
const double mass = 1;        // Masse der Pendel [kg]

/*-------------------------  SIMULATIONS-PARAMETER  ---------------------------*/

const double T_max = 0.6283/4;
double delta_t = T_max; // Zeitliche Schrittweite
//const double T_max = 20.0;
//const double delta_t = 1; // Zeitliche Schrittweite
static const char pos_file_name[] = "position.dat";
static const char energy_file_name[] = "energy.dat";
/*-------------------------  PHYSIKALISCHES SYSTEM  ---------------------------*/

/* TODO */
int pendumlumsODE(double t, const double y[], double f[] , void *params)
{
  for (int i = 0; i < 2*N; i++) {
    f[i]=0;
  }
  for(int i = 0; i < N; ++i){
    f[i] += y[N+i];
  }
  for (int i = 0; i < N-1; i++) {
    double F = k * -(base_length-(y[i+1]-y[i]))/mass;
    f[N+i] += F;
    f[N+i+1] -= F;
  }
  f[N] += -k*y[0]/mass;
  return GSL_SUCCESS;
}
typedef struct {
  double E_kin;
  double E_pot;
  double E_feder;
} Energie;
Energie E;
Energie pendulums_energy(const double y[]){
  E.E_kin =0;
  E.E_pot =0;
  E.E_feder =0;
  for (int i = 0; i < N; i++) {
    E.E_kin += 0.5*mass*pow(y[N+i],2);
    E.E_pot += mass*9.81*(i*base_length-y[i]);
  }
  E.E_feder += k * -y[0]/mass;
  for (int i = 0; i < N-1; i++) {
  E.E_feder += k * (base_length-(y[i+1]-y[i]))/mass;
  }
  return E;
}
int main(void)
{
  printf("T_max %g\n", T_max);
  FILE *fp = fopen("plot.dat", "w");
  FILE *pos_file = fopen(pos_file_name, "w");
  FILE *energy_file = fopen(energy_file_name, "w");


  for (int k = 0; k < 100; k++) {
    delta_t = pow(10,-k* 8.0/99);
    printf("Delta_t: %g K: %i\n",delta_t,k );
    int gsl_dimension = 2*N;//? ? ? ;
    double y[2*N];
    for (int i = 0; i < N; i++) {
      y[i] = i*base_length;
      //yerr[i]=0.1;
    }
    for (int i = 0; i < N; i++) {
      y[N+i] = 0;
      //yerr[N+i]=0.1;
    }
    y[N] = 1;
    /* ------- Simulations-Schleife -------------------------------------------*/
    double t = 0;
    /* #####   HAUPTSCHLEIFE   ##### */
    double periode = 0;
    double per = 0.628;
    double position = 0;
    while (t <= T_max)
    {
      rk2_step(t, delta_t, y, pendumlumsODE, gsl_dimension, NULL);
      /*fprintf(energy_file, "%f,%f,%f,%f\n", t, pendulums_energy(y).E_kin,pendulums_energy(y).E_pot,pendulums_energy(y).E_feder);
      fprintf(pos_file, "%f",t);
      for (int i = 0; i < N*2; i++) {
        fprintf(pos_file, ",%f",y[i]);
      }
      fprintf(pos_file, "\n");
      //Rechnungen aus Aufgabe 19
      if (y[0] <= 0.0 && t != 0.0 && periode == 0.0){
        periode = 2*t;
        printf("Periode: %g\n",periode);
      }
      */
      if (per/4 <= t && t !=0.0 && position == 0.0){
        position = y[0];
        printf("Position: %g\n", position);
        fprintf(fp, "%g,%g\n",delta_t,position);
      }
      //Ende
      t += delta_t;
    }
  }
  fclose(fp);
  fclose(pos_file);
  fclose(energy_file);
  return EXIT_SUCCESS;
}
