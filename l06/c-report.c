#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

//dP/dt = rP(1-P/K)
double func( float t, double P, float r, long K) {
  return r*P*(1.0-P/K);
}

double func_ans( float t, unsigned int P0, float r, unsigned int K){
  return (K*P0*exp(r*t))/(K+P0*(exp(r*t)-1.0));
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main (int argc, char **argv) {
  double k1, k2, k3, k4, P, old_delta_P, delta_P=0;
  float  r, t, delta_t, ans, error, rate_P;
  unsigned int n, tfrom, tto, P0, K, interval=1, true_delta_P, old_P;
  char    ch;
  bool flag=true;

  while (( ch = getopt(argc,argv,"i:")) != -1 ) {
    if (ch == 'i') {  
      interval = atol(optarg);
    }
  }

  printf("P0 r[%] K tfrom tto delta_t> ");
  scanf("%d %f %d %d %d %f", &P0, &r, &K, &tfrom, &tto, &delta_t);

  n = 0;
  t = tfrom;
  P = P0;
  old_P = P0;
  r /= 100;
  puts("###############");
  puts("   n     t         P     true_delta_P  rate_P       ans(error[%])");
  while ( t <= tto ) {
    k1 = delta_t*func(t,P,r,K);
    k2 = delta_t*func(t+delta_t/2,P+k1/2,r,K);
    k3 = delta_t*func(t+delta_t/2,P+k2/2,r,K);
    k4 = delta_t*func(t+delta_t,P+k3,r,K);
    old_delta_P = delta_P;
    delta_P = (k1+2*k2+2*k3+k4)/6.0;
    rate_P = delta_P/old_delta_P;
    if(rate_P<=1.0&&flag==true){
      ans = func_ans(t,P0,r,K);
      error = abst((ans-P)/ans*100);
      true_delta_P = (int)P - old_P;
      printf( "%5d %5.1f %10d %10d %10.5f %10d(%.15f%%) inflection point\n", n, t, (int)P, true_delta_P, rate_P,(int)ans, error);
      old_P = (int)P;
      flag=false;
    }else{
      if( t == (int)t ){
        if ( (int)t % interval == 0 ) {
          ans = func_ans(t,P0,r,K);
          error = abst((ans-P)/ans*100);
          true_delta_P = (int)P - old_P;
          printf( "%5d %5d %10d %10d %10.5f %10d(%.15f%%)\n", n, (int)t, (int)P, true_delta_P, rate_P,(int)ans, error);
          old_P = (int)P;
        }
      }
    }
    n++;
    t = tfrom+delta_t*n;
    P += delta_P; 
  }
  return 0;
}
