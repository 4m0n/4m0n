#include "my_numerics.h"

int farbtest(void){
  printf(BLACK   "BLACK"RESET);
  printf(RED   "RED"RESET); 
  printf(GREEN   "GREEN"RESET);
  printf(YELLOW   "YELLOW"RESET);
  printf(BLUE   "BLUE"RESET);
  printf(MAGENTA   "MAGENTA"RESET);
  printf(CYAN   "CYAN"RESET);
  printf(WHITE   "WHITE"RESET);
  printf(RESET "RESET\n"RESET);
  //BRIGHT 
  printf(BRIGHT BLACK   "BLACK");
  printf(RED   "RED"); 
  printf(GREEN   "GREEN");
  printf(YELLOW   "YELLOW");
  printf(BLUE   "BLUE");
  printf(MAGENTA   "MAGENTA");
  printf(CYAN   "CYAN");
  printf(WHITE   "WHITE\n");
  printf(RESET "RESET\n"RESET);

  //====
  printf(BRIGHT   "BRIGHT"RESET);
  printf(DIM   "DIM"RESET);
  printf(UNDERSCORE   "UNDERSCORE"RESET);
  printf(BLINK   "BLINK"RESET);
  printf(REVERSE   "REVERSE\n"RESET);


  printf(BGblack   "BGblack"RESET);
  printf(BGred   "BGred"RESET);
  printf(BGgreen   "BGgreen"RESET);
  printf(BGyellow   "BGyellow"RESET);
  printf(BGblue   "BGblue"RESET);
  printf(BGmagenta   "BGmagenta"RESET);
  printf(BGcyan   "BGcyan"RESET);
  printf(BGwhite   "BGwhite\n"RESET);

  //Bright

  printf(BRIGHT BGblack   "BGblack");
  printf(BGred   "BGred");
  printf(BGgreen   "BGgreen");
  printf(BGyellow   "BGyellow");
  printf(BGblue   "BGblue");
  printf(BGmagenta   "BGmagenta");
  printf(BGcyan   "BGcyan");
  printf(BGwhite   "BGwhite" RESET);
  printf("\n");
  //=====
  return 1;
}

double diff(double x, double delta, double func(double)){
  return (func(x+delta)-func(x-delta))/(2*delta);
}

double integrate(double left, double right,int N, double integrand(double)){
  double sum = 0;
  double delta_x = (right - left) / N;
  for(int k = 0; k < N; ++k) {
    double x = left + k * delta_x;
    double f = integrand(x);
    //double f = p1(x);
    double A = f * delta_x;
    sum += A;
  }
  return sum;
}

double erf_midpoint(double left, double right,int N, double funktion(double)){
  double y = 0;
  double delta_x = (right - left) / N;
  for (int k = 1; k<N+1; ++k){
    y = y+ funktion(left+k*delta_x + delta_x/2)*delta_x ;
  }
  return y;
}

double erf_simpson(double left, double right,int N, double funktion(double)){
  double y = 0;
  double delta_x = (right - left) / N;
  for (int k = 1; k<N+1; ++k){
    y = y + (delta_x/6)*(funktion(left+k*delta_x)+4.0*funktion(left+k*delta_x+0.5*delta_x)+funktion(left+k*delta_x+delta_x));
    //y = y+ funktion(left+k*delta_x + delta_x/2)*delta_x;
  }
  return y;
}

double modulo(double a, double b){ //mit Double
  int i = 0;
  while (b*i < a){
    i++;
    printf("%f\n", a - b*(i-1));
  }
  return a - b*(i-1);
}

double diff2(double x, double t, double delta, double func(double,double)){
  return (func(x+delta,t)-func(x-delta,t))/(2*delta);
}

double bisektion(FILE *fp, double a, double b, double t, double stop, double func(double,double)){

  if (func(a,t)*func(b,t)>0){
    printf("Die Werte liefern keine Nullstellen mit diesem Verfahren\n");
    return 0.0;
  }
  int i =0;
  double x = 0;
  while (fabs(func(a,t))>=stop && fabs(func(b,t))>= stop){
    i++;
    x = (a+b)/2;
    if (func(x,t)*func(a,t)<0){
      b=x;
    }
    else if(func(x,t)*func(b,t)<0){
      a=x;
    }
    else if(func(a,t)*func(b,t)*func(x,t)==0){
      printf("Wähle ein anderes Intervall!");
      return 0;
    }
    if (fp != NULL){
      fprintf(fp,"%i,%f\n",i,fabs(x-(b+a)/2));
    }
  }
  return (b+a)/2;
}

double newton_raphson(double a, double stop, double func(double)){
  double x = a;
  int i = 0;
  while (fabs(func(x))>=stop){
    i++;
    x = x- func(x)/diff(x,stop,func);
  }
  return x;
}

double random_uniform(double a, double b){
  static gsl_rng* generator = NULL;

  if (generator == NULL){
  generator = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(generator, time(NULL));
  }
  if (a > b){
    double u = b;
    b = a;
    a = u;
  }
  double diff = b - a;
  double x = (gsl_rng_uniform(generator)*fabs(diff) + a);
  return x;
}

Tuple random_gaussian(void){ //glaub ich
  double r = 2;
  double u;
  double v;
  do{
    u = random_uniform(-1,1);
    v = random_uniform(-1,1);
    r = u*u+v*v;
  }while(r>1 || r == 0);
  Tuple num;
  double m = sqrt((-2*log(r))/(r));
  num.x = u *m;
  num.y = v *m;
  return num;
}

double mc_integrate(double func(double* ,int), double a[], double b[], int dim, int N){
  double v = 1;

  for (int i = 0; i<dim;i++){
    v = v*(b[i]-a[i]);
  }
  double summe =0;
  double y[dim];
  double prozent = 0;
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < dim; i++) {
      y[i]= random_uniform(a[i], b[i]);
    }
    summe = summe + func(y,dim);
    if (k == (int)(N*prozent)){
      //printf("\n%g Prozent", prozent*100);
      prozent = prozent + 0.1;
    }
  }
  summe = v/N * summe;
  return summe;
  }

double heaviside(double x, double y, double a[], double b[]){
  //printf("x: %f y: %f\n",x*x+y*y );
  //if (fabs(x) < fabs(a[0]) && fabs(y) <fabs(b[0])){
  if (x*x+y*y <=1){
    return 1.0;
  }
  else {
    return 0.0;
  }
}

double mittelpunktsregel(double func(double ,double), double a[], double b[], int dim, double delta, double N[]){
  double summe =0;
  double prozent = 0; //für mehr spaß beim ausführen
  for (int i = 1; i <= N[0]; i++) {
    for (int j = 1; j <= N[1]; j++) {
      double x = a[0] +(i-0.5)*delta;
      double y = b[0] +(j-0.5)*delta;
      summe = summe +func(x,y)*heaviside(x,y,a,b);

    }
    if (i == (int)((N[0]+N[1])/2 *prozent)){
      //printf("\n%g Prozent", prozent*100);
      prozent = prozent + 0.1;
    }
  }
  summe = summe*delta*delta;
  //printf("\nSumme i: %f\n",summe);
  return summe;
}
//=========================================

//            Steps

//=========================================
void euler_step(double t, double delta_t ,double y[], ode_func func, int dim, void *params){
  double *f = calloc(dim, sizeof(double));
  func(t, y, f, params);

  for (int i = 0; i < dim; i++) {
    y[i] = y[i] + delta_t*f[i];
  }
  free(f);
}

void rk2_step(double t, double delta_t, double y[], ode_func func, int dim, void*params){
  double support[dim];
  double k1[dim];
  double k2[dim];
  double *f = calloc(dim, sizeof(double));
  func(t, y, f, params);
  for (int i = 0; i < dim; i++) {
    k1[i] = delta_t*f[i];
  }
  //=================

  for (int i = 0; i < dim; i++) {
    support[i] = y[i]+k1[i]/2;
  }

  func(t+delta_t/2, support, f, params);
  for (int i = 0; i < dim; i++) {
    k2[i] = delta_t*f[i];
  }
  //================

  for (int i = 0; i < dim; i++) {
    y[i]= y[i]+k2[i];
  }
  free(f);

}

void rk4_step(double t, double delta_t, double y[], ode_func func, int dim, void*params){
  double support[dim];
  double k1[dim];
  double k2[dim];
  double k3[dim];
  double k4[dim];
  double *f = calloc(dim, sizeof(double));

  func(t, y, f, params);
  for (int i = 0; i < dim; i++) {
    k1[i] = delta_t*f[i];
  }
  //=================
  for (int i = 0; i < dim; i++) {
    support[i] = y[i]+k1[i]/2;
  }
  func(t+delta_t/2, support, f, params);
  for (int i = 0; i < dim; i++) {
    k2[i] = delta_t*f[i];
  }
  for (int i = 0; i < dim; i++) {
    support[i] = y[i]+k2[i]/2;
  }
  func(t+delta_t/2, support, f, params);
  for (int i = 0; i < dim; i++) {
    k3[i] = delta_t*f[i];
  }
  for (int i = 0; i < dim; i++) {
    support[i] = y[i]+k3[i];
  }
  func(t+delta_t, support, f, params);
  for (int i = 0; i < dim; i++) {
    k4[i] = delta_t*f[i];
  }
  //================
  for (int i = 0; i < dim; i++) {
    y[i] = y[i]+1.0/6.0*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }

  free(f);

}

void verlet_step(double t,double delta_t,double y[], ode_func func,int dim, void*params){
  double a1[dim/2];
  double a2[dim/2];
  double *f = calloc(dim, sizeof(double));
  func(t, y, f, params);
  for (int i = 0; i < dim/2; i++) {
    a1[i]=f[dim/2+i];
  }
  for (int i = 0; i < dim/2; i++) {
    y[i] = y[i]+y[dim/2+i]*delta_t+a1[i]*((delta_t*delta_t)/2);
  }

  func(t+delta_t, y, f, params);
  for (int i = 0; i < dim/2; i++) {
    a2[i]=f[dim/2+i];
  }
  for (int i = 0; i < dim/2; i++) {
    y[dim/2+i]=y[dim/2+i]+(delta_t/2)*(a2[i]+a1[i]);
  }
  free(f);
}

int signum(double x){
  if (x > 0){
    return 1;
  }
  else if (x <0){
    return -1;
  }
  else {
    return 0;
  }
}

//=========================================

//            MATRIX ZEUGS

//=========================================
int printMatrix(int n, int m, double A[n*m],char *label){ 
  int z = 0;
  printf("\n  ");
  for (int i = 0; i < n-1; i++){
    printf("          ");
    if(i*2.0+4 == n){  
      printf(BRIGHT UNDERSCORE RED"Matrix print:" RESET);
      printf(" ");
      printf(BRIGHT CYAN"%s",label);
      printf(RESET"");
    }
  }  

  printf("\n");
  printf(BRIGHT YELLOW"-----");
  for (int i = 0; i < m; i++) //Nummerierung der Zeilen
  {
    printf("-%.2i)------",i+1);
  }
  printf("\n"RESET);
  for (int k = 0; k < n; k++) { 
    printf(BRIGHT YELLOW"%.2i) |"RESET,k+1); //Nummerierung der Spalten
    for (int i = 0; i < m; i++) {
      if (A[z] >= 0) //erstes Zeichen Vorzeichen check
      {
        printf(" ");
      }
      if (n==m && z == i*n+i){
        printf(BRIGHT BGgreen"%#.3f",A[z]);
        printf(RESET"");
      }
      else{
        printf("%#.3f", A[z]);
      }
      if (fabs(A[z])<10){
        printf("   ");
      }
      else if (fabs(A[z])<100){
        printf("  ");
      }
      else if (fabs(A[z])<1000){
        printf(" ");
      }
      z++;
      printf(YELLOW BRIGHT"|"RESET);
    }
  printf("\n");
  }

  for (int i = 0; i < m-1; i++) //Nummerierung der Zeilen
  {
    printf(BRIGHT YELLOW"-----------");
  }
  printf("------\n"RESET);
  return 0;
}

double matrixmult(int n, double A[n*n], double B[n*n],double C[n*n]){ //C = A*B -> C leer übergeben !!Nur für Quadratische Matrizen!!

  for (int i = 0; i < n*n; i++){
    C[i]=0;
  }

  for (int i = 0; i < n; i++){
    for (int k = 0; k < n; k++){
      for (int j = 0; j < n; j++){
        C[i*n+k]= C[i*n+k] + A[i*n+j] * B[j*n+k];
      }
    }
  }
  return 1;
}

int gauss(int n, int m,double A[n*m], int pivoting){
  //printMatrix(n,m,A,"");
  int vz = 1; // 1 unverändert -1 verändert
  if (pivoting){
    for (int i = 0; i < n-1; i++){
      for (int k = i+1; k < n; k++){
        if ( fabs(A[i*m+i])<fabs(A[k*m+i])){
          vz = vz * -1;
          for (int j = 0; j < m; j++){
            double temp = A[i*m+j];
            A[i*m+j]=A[k*m+j];
            A[k*m+j]=temp;
          } 
        }
      }
    }
  }
  for (int i = 0; i < n-1; i++){   
    for (int k = i+1; k < n; k++){ 
      double c = A[k*m+i]/A[i*m+i];
      for (int j = 0; j < m; j++){
        A[k*m+j] = A[k*m+j] - c*A[i*m+j];
      } 
    }
  }
  return vz;
}

double det(int n, double A[n*n],int pivoting){

  double A_2[n*n];
  for (int i = 0; i < n*n; i++)
  {
    A_2[i]=A[i];
  }
  
  double sign = gauss(n,n,A_2,1);
  for (int i = 0; i < n; i++) {
    sign *= A_2[n*i+i];
  }  
  printMatrix(10,10,A_2,"Gauss");
  return sign;
}

void lgs_solve(int n, double A[n*n],double b[n], double x[n],int pivoting){
  double *C = (double*)malloc(n*(n+1)*sizeof(double));
  //printf("test");
  //printf("%s %p\n",__func__, A);
  int z = 0;
  for (int i = 0; i < n*n; i++)
  {
    if (i == n*(z+1)){
      z++;
    }
    C[i+z] = A[i];
  }
  for (int i = 0; i < n; i++)
  {
    C[i*(n+1)+n]=b[i];
  }
  printMatrix(n,n+1,C,"Davor");
  gauss(n,n+1,C,1);
  printMatrix(n,n+1,C,"Danach");
  x[n-1]=C[n*(n+1)-1]/C[n*(n+1)-2];
  for (int i = n-2; i >= 0; i--)
  {
    double temp =0;
    for (int j = i+1; j < n; j++)
    {
      temp += C[i*(n+1)+j]*x[j];
    }
    x[i]= 1/C[i*(n+1)+i]*(C[i*(n+1)+n]-temp);
  }
  free(C);
  return;
}

void inverse(int n, double A[n*n], double A_inverse[n*n]){
  if (det(n,A,1)==0){
    printf("Determinate ist Null, du Null!");
    return;
  }
  double b[n];
  double x[n];
  //printMatrix(n,n,A,"");

  for (int i = 0; i < n; i++)
  {
    for (int u = 0; u < n; u++)
    {
      b[u]=0;
    }
    b[i]=1;

    
    lgs_solve(n,A,b,x,1);
    for (int k = 0; k < n; k++)
    {
      A_inverse[k*n+i]=x[k];
    }
    
  }
  printf("\nInverse\n");
  printMatrix(n,n,A_inverse,"");
  printf("\nMult\n");
  double C[n*n];
  matrixmult(n,A,A_inverse,C);
  printMatrix(n,n,C,"");
}

double solve_linear_system(lapack_int n){
  lapack_int info,m=n,lda=m,ldb=1,nrhs=1;
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
  return 0;
}

void lgs_jacobi_solve(int n, double A[], double b[], double x[], int k_max){
  double *x1 = (double *)malloc(n*sizeof(double)); 
  for (int k = 0; k < k_max; k++){
    for (int i = 0; i < n; i++){
      x1[i] = 0;
      for (int j = 0; j < n; j++){
        if (i != j){
          x1[i] -= A[i*n+j] * x[j];
        }
      }
      x1[i]= 1/A[i*n+i] * (b[i]-x1[i]);
    }
    for (int i = 0; i <n; i++){
      x[i] = x1[i]; //Wieder in x übertragen
    }
  }
  free(x1);
  return 1;
}

void lgs_gs_solve(int n, double A[], double b[], double x[], int k_max){
  double sum;
  for(int k=0;k<k_max;k++)
  {
    for(int i=0;i<n;i++)
    {
      sum=0;
      for(int j=0;j<n;j++)
      {
        if(i!=j){
          sum-=A[i*n+j]*x[j];
        }
      }
      x[i]=b[i]+sum;
      x[i]= x[i]/A[i*n+i];
    }
  }
  return;

}