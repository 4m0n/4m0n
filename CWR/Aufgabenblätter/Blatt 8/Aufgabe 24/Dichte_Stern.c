#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "../../../Funktionen/my_numerics.h"


#define nerviges_printzeug_dass_ich_nicht_jedes_mal_neu_eingeben_will_weil_es_mir_zu_lang_ist fp, "%f,%f,%f,%f\n",r/R_s,y[0]/100,y[1]/mass_s,y[2]
//===== STARTWERTE UND VARIABLEN =====
const double gamma_0 = 4.0/3.0;
const double kappa = 3.85e9;
// ==== Werte für die Sonne
// Die werte zu 1 setzen, wenn man den von der Aufgabe verlangten Plot haben will, so sind die Ergebnisse immer in relation zu Sonne
const double mass_s = 1.989e30;//Sonnenmasse
const double R_s = 7e8; //Radius Sonne -> NICHT ÄNDERN
const double rho_s = 1.5e5; //Dichte Sonne -> nicht errechnet -> nur für schönere Plots. rho_s = 1 setzen, für das wahre Ergebnis
const double temp_s = 9.3e6; // Sonne Temp
// ==== berechnung aller daraus folgenden STARTWERTE

const double R = 1.2 * R_s; //Radius Stern
const double G = 6.67384e-11;
const double epsilon = 1e-4;
const double delta_r = 1000;
double mass_star = 1; // Masse vom Stern rho = 20k. Wird später für Bonus benötigt
double rho_0 = 70000;//70000;
double r = epsilon; //Wegen Bonus aufgabe jetzt leider global :((( -> funktioniert aber trotzdem nicht
int check = 0; // Boolean -> 0 = False, 2 == True (hatte vorher  == 1, hab jz aber soviel verändert das ich es bei >1 lasse)
int rohODE(double r, const double y[], double f[] , void *params){

  f[0] = -3.0/(2.0*kappa*gamma_0) * pow(y[0],2.0-gamma_0) * (G*(y[1]))/pow(r,2.0);
  f[1] =  4.0*M_PI*y[0]*pow(r,2.0);
  if (check > 1){
    f[2] = -0.5*gamma_0/kappa * G * (f[1])/(delta_r);
  }
  return 1;
}

double radiusberechnen(double rho_0){
  int dim = 2;
  if (check > 1){
    dim = 3;
  }
  double y[dim];
  r = epsilon;
  y[0] = rho_0;
  y[1] = rho_0* 4.0/3.0 * M_PI * pow(epsilon,3);
  if (check > 1){
  y[2] = 0.5*gamma_0/kappa * G * mass_star/R;
  printf("Start Temp: %f ",y[2]); //hier kommt bereits eine etwas merkwürdige Starttemp raus. (Beweis das die Nasa lügt?)

  }
  printf("Start Dichte: %f ",y[0]);
  FILE *fp = fopen("plot.dat","w"); //es ist sinnlos die Datei immer neu zu erstellen, aber wenn ich den ganzen Spaß in eine Abfrage packe ist "fp undeclared".
  int i =0;
  int step = 1;

  while (y[0]>0.1){
    i++;
    rk4_step(r, delta_r, y, rohODE, dim, NULL);
    if (i == step && check > 1){
      fprintf(nerviges_printzeug_dass_ich_nicht_jedes_mal_neu_eingeben_will_weil_es_mir_zu_lang_ist);
      step = step+1000;
    }
    r+=delta_r;
  }
  fprintf(nerviges_printzeug_dass_ich_nicht_jedes_mal_neu_eingeben_will_weil_es_mir_zu_lang_ist);
  mass_star = y[1];
  fclose(fp);
  printf("Sternradius: %f\n\n",r);

  return fabs(R-r);
}


int main(void){
  printf("Start newton_raphson zum ermitteln der richtigen Dichte.\n");
  rho_0 = newton_raphson(rho_0,0.1,radiusberechnen);
  check = 2;
   //damit die Daten in die Datei geschrieben werden
  printf("\n\n==== PLOT RECHNUNG ====\n\n\nRadius differenz: %f\nbei einer Dichte von %f",radiusberechnen(rho_0),rho_0);
}
