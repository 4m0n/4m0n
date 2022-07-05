#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "../../../Funktionen/my_numerics.h"

/*------------------------  PHYSIKALISCHE KONSTANTEN  -------------------------*/

const int N = 1;              // Anzahl der Pendel
const double k = 100;           // Federhaerte [N/m]
//=========== Reibungskoeffizienten =======
const double mu_s = 0.55;//-9.3;      //Haftreibung
const double mu_k = -0.02;     // Gleitreibung
//double b = -0.2;    // Viskositätsding => Wird aufgrund von Aufgabe 2 erst in der Funktion definiert.
//=========================================
const double base_length = 1; // Basislaenge der Federn [m]
const double mass = 1;        // Masse der Pendel [kg]
const double normalkraft = mass * 9.81;

/*-------------------------  SIMULATIONS-PARAMETER  ---------------------------*/
double T_max = 20; // nicht const damit es die Zeit für Aufgabe 1 und 2 besser angepasst werden kann.
double delta_t = 1e-3; // Zeitliche Schrittweite

//um nur eine pendumlumsODE zu haben.
int aufgabenteil;
const char name[10][30] = {"Haftreibung","Gleitreibung","Viskosität","Haft und Gleit","Alle 3 Kräfte","Viskos + Gleit","Visko + Haft","b<2m*omega","b=2m*omega","b>2m*omega"}; //die ersten 5 für Aufgabe 1 die danach für Aufgabe 2


int pendumlumsODE(double t, const double y[], double f[] , void *params)
{
  for (int i = 0; i < 2*N; i++) {
    f[i]=0;
  }
  for(int i = 0; i < N; ++i){
    f[i] += y[N+i];
  }
  double F_reibung =0;
  double F_haft = 0;
  double b = -0.2;
  for (int i = 0; i < N; i++) {

    double v = y[N];
    if (i > 0){
      v = y[N+i-1]; // besser für die Fehlersuche
    }


    // ===== Grundkärfte =====
    if (aufgabenteil == 0){
      F_haft = 5; //groß wählen damit sie auftritt
      F_haft = -F_haft * normalkraft; //-F_haft * N HAFTREIBUNG  !!
      F_reibung = 0; // Spielt nur eine Rolle wenn auf den Körper eine zu geringe Kraft wirkt
    }
    else if (aufgabenteil == 1){
      F_reibung = -mu_k*normalkraft* signum(v); // -mu_k * N * abs(v) GLEITREIBUNG
    }
    else if (aufgabenteil == 2){
      F_reibung = - b * v; //-b*v VISKOSREIBUNG
    }
    //===== Mix aus Grundkräften =====
    else if( aufgabenteil == 3){ //Haftreibung + Gleitreibung
      F_haft = mu_s;
      F_haft = -F_haft * normalkraft;
      F_reibung = 0;
      F_reibung += -mu_k*normalkraft* signum(v);
    }
    else if( aufgabenteil == 4){ //Haftreibung + Gleitreibung + Viskosität
      F_haft = mu_s;
      F_haft = -F_haft * normalkraft;
      F_reibung = 0;
      F_reibung += -(mu_k*normalkraft* signum(v) + b * v);
    }

    else if( aufgabenteil == 5){ //Viskosität + Gleitreibung
      F_reibung = 0;
      F_reibung += -mu_k*normalkraft* signum(v) - b * v;;
    }
    else if( aufgabenteil == 6){ //Viskosität + Haftreibung
      F_haft = mu_s;
      F_haft = -F_haft * normalkraft;
      F_reibung = 0;
      F_reibung += - b * v;
    }

    // ==== Aufgabe 2 ====
    else if (aufgabenteil == 7){
      b = -2*mass*sqrt(k/mass)/2;
      F_reibung = - b * v; // b<2m*omega
    }
    else if (aufgabenteil == 8){
      b = -2*mass*sqrt(k/mass);
      F_reibung = - b * v; // b=2m*omega
    }
    else if (aufgabenteil == 9){
      b = -2*mass*sqrt(k/mass)*2;
      F_reibung = - b * v; // b>2m*omega
    }
    // ==== Ende ====
    else {
      printf("\n\n==Error==\n\n");
    }
    //===== Berechnung der resultierenden Kraft =====
    double F_eindim = (-k*y[0]/mass);
    double F = F_eindim;
    if (i > 0){
      F = (k * -(base_length-(y[i]-y[i-1]))/mass);
    }

    int stopp = 1; //Wieder notwendig für den Eindimensionalen Fall

    if ((fabs(F) <= fabs(F_haft) && fabs(v) <= 1e-2)){
      F = 0;
      F_eindim = 0;
      F_reibung = 0;
      stopp = 0;
      for (int l = 0; l < 2*N; l++) { //da ich nicht direkt von v = 0 ausgehe sondern eine kleine Tolleranz zulasse, muss ich hier etwas nachhelfen
        f[l]=stopp;
      }
    }
    F = (F - F_reibung)*stopp;
    if (i > 1){
      f[N+i-1] += F;
      f[N+i] -= F;
    }

    f[N] = (F_eindim-(F_reibung))*stopp;
  }

  return GSL_SUCCESS;
}

int aufgabe1(void){
  printf("\n==== Aufgabe 1 ==== \n");
  int num = 7; //Anteil von Kombinationen an Reibungskräften
  T_max = 20;
  FILE * info = fopen("info.txt","w"); //Damit man nichts im Python script anpassen muss -> eine Datei mit Informationen über alles was notwendig ist
  fprintf(info, "%i,%i,%i",num,N,1); // letzte i steht für Aufgabe 1

  FILE *fp[num];
  char filename[64];
  for (int k = 0; k < num; k++) {
    sprintf(filename,"plot%d.txt",k+1);
    fp[k]=fopen(filename, "w");
  }

  for (int i = 0; i < num; i++) {
    printf("Reibungskräfte: %s\n",name[i]);
    aufgabenteil = i;
    fprintf(info, ",%s",name[i]);
    double t = 0;
    int gsl_dimension = 2*N; ;
    double y[2*N];
    for (int i = 0; i < N; i++) {
      y[i] = -i*base_length; //unwichtig ob + oder -
    }
    for (int i = 0; i < N; i++) {
      y[N+i] = 0;
    }
    y[N]=1;
    while (t <= T_max)
    {
      rk2_step(t, delta_t, y, pendumlumsODE, gsl_dimension, NULL);
      fprintf(fp[i], "%g",t);
      for (int k = 0; k < N; k++) {
        fprintf(fp[i], ",%g",y[k]);
      }
      fprintf(fp[i],"\n");
      t += delta_t;
    }
  }
  fclose(info);
  for (int k = 0; k < num; k++) {
    fclose(fp[k]);
  }
  printf("\n==> make plot (der Plot wird mit Aufgabe 2 überschrieben. ggf den Bildnamen ändern.)\n\n");
  return 0;
}

int aufgabe2(void){
  printf("\n==== Aufgabe 2 ====\n");
  int num = 3; //3 Fälle für b
  T_max = 5;
  int num_skip = 7; //wichtig, num_skip muss mit der Anzhal an verwendeten Kombinationen aus Augabe 1 übereinstimmen. Hätte man auch automatisieren können, aber dann hätte ich noch eine Globale Variable gebraucht oder hätte den code generell umschreiben können/müssen
  FILE * info = fopen("info.txt","w"); //Damit man nichts im Python script anpassen muss -> eine Datei mit Informationen über alles was notwendig ist
  fprintf(info, "%i,%i,%i",num,N,2); //siehe Aufgabe 1


  FILE *fp[num];
  char filename[64];
  for (int k = 0; k < num; k++) {
    sprintf(filename,"plot%d.txt",k+1);
    fp[k]=fopen(filename, "w");
  }

  for (int i = 0; i < num; i++) {
    printf("Reibungskräfte: %s\n",name[i+num_skip]);
    aufgabenteil = i+num_skip;
    fprintf(info, ",%s",name[i+num_skip]);
    double t = 0;
    int gsl_dimension = 2*N; ;
    double y[2*N];
    for (int i = 0; i < 2*N; i++) {
      y[i] = i*base_length;
    }

    while (t <= T_max)
    {
      rk2_step(t, delta_t, y, pendumlumsODE, gsl_dimension, NULL);
      fprintf(fp[i], "%g",t);
      for (int k = 0; k < N; k++) {
        fprintf(fp[i], ",%g",y[k]);
      }
      fprintf(fp[i],"\n");
      t += delta_t;
    }
  }
  fclose(info);
  for (int k = 0; k < num; k++) {
    fclose(fp[k]);
  }
  printf("\n==> make plot (altes Bild wird überschrieben)\n\n");
  return 0;
}

int main(void){

  int aufgabe = 1;
  printf("\nLeider kam ich auf die scanf Idee erst ganz am ende, deshalb ist das Programm nicht darauf angepasst und man muss jedes mal das Programm abbrechen zum Plotten. Nächste mal mach ich das etwas sinnvoller.\n");
  while (aufgabe ==1 || aufgabe == 2){
    printf("Aufgabe 1 => 1 \nAufgabe 2 => 2\nBeenden => 3 \nEingabe:");
    scanf("%i", &aufgabe);
    printf("\nEs wird ausgeführt, Aufgabe: %i\n",aufgabe);
    if (aufgabe == 1){
      aufgabe1();
    }
    else if (aufgabe == 2){
      aufgabe2();
    }
    else if(aufgabe != 3){
      printf("Das war falsch.");
      goto a;
    }
  }

  if (1 == 0){ // wird ausgeführt wenn man keine der entsprechenen Zahlen eingibt (dazu passend das Bild)
    a:
    char buffer[100];
    FILE *file = fopen("schwachsinn.dat", "r");
    if (file == NULL)
    {
      fputs("Failed to open the file\n", stderr);
      return -1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
      printf("%s", buffer);
    }

    fclose(file);
    printf("\n\n\nTerminal auf einem Großen Bildschirm im Vollbild Modus verwenden.\nUnd %i stand nicht zur auswahl.", aufgabe);
  }


}
