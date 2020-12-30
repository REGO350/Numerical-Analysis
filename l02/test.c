#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
  int count = 100;
  float x[count], y[count];
  int i;
  for(i=0;i<count;i++){
    x[i] = i;
    y[i] = 2*i;
  }
  FILE *gnuplot = popen("gnuplot", "w");
  fprintf(gnuplot, "plot '-'\n");
  for (i = 0; i < count; i++)
      fprintf(gnuplot, "%f %f\n", x[i], y[i]);
  fprintf(gnuplot, "e\n");
  fflush(gnuplot);
  sleep(1000);



  int A = 1, N = 20, i=0;
  float dt = 0.01, T = 2*M_PI;
  double y = A/2;
  for(i=0;i<N;i++){
    y += -A/(M_PI*i)*sin(2*M_PI*i*x/T);
  }
  return y-A/2;
}