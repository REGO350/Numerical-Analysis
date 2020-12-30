#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double func( double t, double x )
{
  return t + x;
}


int main (int argc, char **argv) {
  double  t, x, k1, k2, delta_x;
  double  tfrom, tto, delta_t;
  int	  n, tsteps;
  
  printf("t0 x0 tto tsteps> ");
  if ( argc >= 5 ) {
    tfrom = atof( argv[1] );
    x     = atof( argv[2] );
    tto   = atof( argv[3] );
    tsteps = atof( argv[4] );
    printf( "%lf %lf %lf %d\n", tfrom, x, tto, tsteps );
  } else {
    scanf( "%lf %lf %lf %d", &tfrom, &x, &tto, &tsteps );
  }	/* delta_t には２の累乗分の１を使う */

  delta_t = (tto-tfrom)/tsteps;
  n = 0;
  t = tfrom;
  while ( t <= tto ) {
    /* k1 の計算 */
    k1 = delta_t*func(t,x); /* (2-A) */
    /* k2 の計算 */
    k2 = delta_t*func(t+delta_t,x+k1); /* (2-B) */ 
    /* delta_x の計算 */
    delta_x = (k1+k2)/2.0; /* (2-C) */
    printf( "%5d %20.14lf %20.14lf %20.14lf\n", n, t, x, delta_x );
    /* n の更新 */
    n++; /* (1-B) */
    /* t の更新 */
    t = tfrom+delta_t*n; /* (1-C) */ /* 誤差の累積を避けるように工夫すること */
    /* x の更新 */
    x += delta_x; /* (1-D) */
  }

  return 0;
}
