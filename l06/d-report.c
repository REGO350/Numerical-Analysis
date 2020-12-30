#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* dx2/dt = f(x1, x2, t)*/
double func_dx2_dt(double t, double x1, double x2)
{
  return -20.0*x1-t*x2;
}

/* dx1/dt = x2 */
double func_dx1_dt(double t, double x1, double x2)
{
  return x2;
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main (int argc, char **argv) {
  double  t, tfrom, tto, delta_t;
  double  x1, k1_1, k2_1, k3_1, k4_1, delta_x1;
  double  x2, k1_2, k2_2, k3_2, k4_2, delta_x2;
  int	  n, interval=1, tsteps, q;

  printf("tfrom x1_0 x2_0 tto tsteps=2^q> ");
  scanf("%lf %lf %lf %lf %d", &tfrom, &x1, &x2, &tto, &q);

  n = 0;
  t = tfrom;
  tsteps = pow(2, q);
  interval = tsteps/2;
  delta_t = 1.0/(tsteps);
  while (t <= tto) {
    /* k1 for x1 の計算 */
    k1_1 = delta_t*func_dx1_dt(t,x1,x2);/* (4-A-1) */ 
    /* k1 for x2 の計算 */
    k1_2 = delta_t*func_dx2_dt(t,x1,x2);/* (4-A-2) */ 
    /* k2 for x1 の計算 */
    k2_1 = delta_t*func_dx1_dt(t+delta_t/2.0,x1+k1_1/2.0,x2+k1_2/2.0);/* (4-B-1) */
    /* k2 for x2 の計算 */
    k2_2 = delta_t*func_dx2_dt(t+delta_t/2.0,x1+k1_1/2.0,x2+k1_2/2.0);/* (4-B-2) */
    /* k3 for x1 の計算 */
    k3_1 = delta_t*func_dx1_dt(t+delta_t/2.0,x1+k2_1/2.0,x2+k2_2/2.0);/* (4-C-1) */
    /* k3 for x2 の計算 */
    k3_2 = delta_t*func_dx2_dt(t+delta_t/2.0,x1+k2_1/2.0,x2+k2_2/2.0);/* (4-C-2) */
    /* k4 for x1 の計算 */
    k4_1 = delta_t*func_dx1_dt(t+delta_t,x1+k2_1,x2+k2_2);/* (4-D-1) */
    /* k4 for x2 の計算 */
    k4_2 = delta_t*func_dx2_dt(t+delta_t,x1+k2_1,x2+k2_2);/* (4-D-2) */
    /* delta_x for x1 の計算 */
    delta_x1 = (k1_1+k2_1*2.0+k3_1*2.0+k4_1)/6.0;/* (4-E-1) */
    /* delta_x for x2 の計算 */
    delta_x2 = (k1_2+k2_2*2.0+k3_2*2.0+k4_2)/6.0;/* (4-E-2) */
    /* 途中結果の表示 */
    if ( n % interval == 0 ) {
      printf( "%20.14lf %20.14lf %20.14lf %20.14lf %20.14lf\n", t, x1, x2, delta_x1, delta_x2);
    }
    /* n の更新 */
    n++; /* (3-F) */
    /* t の更新 */
    t = abst(tfrom+delta_t*n);/* (3-G) */
    /* x の更新 */
    x1 += delta_x1;/* (4-F-1) */
    x2 += delta_x2;/* (4-F-2) */
  }
  return 0;
}
