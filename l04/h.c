#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Lagrange n Point Interpolation */
double func(double x){
  return 1/(1+25*pow(x,2));
}

int main(void){
  int n,i,j;
  printf("order n> "); scanf("%d", &n);
  n++;
  double x[n], f[n], X, F, k;
  for(i=0;i<n;i++){
    printf("x%d> ", i);
    scanf("%lf", &x[i]);
    f[i] = func(x[i]);
  }
  printf( "x for f(x)> " );
  while(scanf( "%lf", &X ) != EOF){
    F=0.0;
    for(i=0;i<n;i++){
      k=1.0;
      for(j=0;j<n;j++){
        if(j!=i){
          k*=(X-x[j]);
          k/=(x[i]-x[j]);
        }
      }
      F+=k*f[i];
    }
    printf( "f(%lf) = %lf\n", X, F );
    printf( "x for f(x)> " );
  }
  printf("\n");
  return 0;
}