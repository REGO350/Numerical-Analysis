#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double func( double t, double x )
{
  return t * x; /*  dx/dt = func(t,x) */
}  

double func_ans(double t){
  return exp(1/2*pow(t,2));
}


int main (int argc, char **argv) {
  double  t, x, k1, k2, delta_x;
  double  tfrom, tto, delta_t, ans, error; 
  int	  n;

  
  printf("t0 x0 tto delta_t> ");
  if ( argc >= 5 ) {
    tfrom = atof( argv[1] );
    x     = atof( argv[2] );
    tto   = atof( argv[3] );
    delta_t = atof( argv[4] );
    printf( "%lf %lf %lf %lf\n", tfrom, x, tto, delta_t );
  } else {
    scanf( "%lf %lf %lf %lf", &tfrom, &x, &tto, &delta_t );
  }				/* h には２の累乗分の１を使う */

  n = 0;
  t = tfrom;
  while ( t <= tto ) {
    /* k1 の計算 */
    k1 = delta_t*func(t,x); /* (2-A) */
    /* k2 の計算 */
    k2 = delta_t*func(t+delta_t,x+k1); /* (2-B) */ 
    /* delta_x の計算 */
    delta_x = (k1+k2)/2.0; /* (2-C) */
    printf( "%5d %20.14lf %20.14lf %20.14lf %20.14lf(%.10lf%%)\n", n, t, x, delta_x, ans, error);
    /* n の更新 */
    n++; /* (1-B) */
    /* t の更新 */
    t = tfrom+delta_t*n; /* (1-C) */ /* 誤差の累積を避けるように工夫すること */
    /* x の更新 */
    x += delta_x; /* (1-D) */
    ans = func_ans(t);
    error = (ans-x)/ans*100;
  }

  return 0;
}
