#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func( double t, double x ){
  return t*x;
}

double func_ans(double t){
  return 
}

int main (int argc, char **argv) {
  double  x, t, k1, k2, k3, k4, delta_x, ans, error;
  double  tfrom, tto, delta_t;
  int	  n;

  printf("tfrom x0 tto delta_t> ");
  scanf("%lf %lf %lf %lf", &tfrom, &x, &tto, &delta_t);

  n = 0;
  t = tfrom;
  while ( t <= tto ) {
    /* k1 の計算 */
    k1 = delta_t*func(t,x);/* (3-A) */
    /* k2 の計算 */
    k2 = delta_t*func(t+delta_t/2,x+k1/2);/* (3-B) */
    /* k3 の計算 */
    k3 = delta_t*func(t+delta_t/2,x+k2/2);/* (3-C) */
    /* k4 の計算 */
    k4 = delta_t*func(t+delta_t,x+k3);/* (3-D) */
    /* delta_x の計算 */
    delta_x = (k1+2*k2+2*k3+k4)/6.0;/* (3-E) */
    /* 途中結果の表示 */
    ans = func_ans(t);
    error = (ans-x)/ans*100;
    printf( "%5d %20.14lf %20.14lf %20.14lf %20.14lf(%.10lf%%)\n", n, t, x, delta_x, ans, error);
    /* n の更新 */
    n++;/* (3-F) */
    /* t の更新 */
    t = tfrom+delta_t*n;/* (3-G) */
    /* x の更新 */
    x += delta_x; /* (3-H) */

  }
  return 0;
}
