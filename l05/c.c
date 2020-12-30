#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ガウス 3 点公式 */


double fun( double x )
{
  return  sin( x );
}

double FUN(double x)
{
  return -cos(x);
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

double scale( double c, double a, double b )
{
  return (a*(1.0-c)+b*(1.0+c))/2.0;
}

int main ( int argc, char **argv ) {
  double  x1, x2, x3, f1, f2, f3, G;
  double  a, b, h;
  double  SUM, diff, diff_percent;
  double  xfrom, xto;
  int	  xsteps, xidx;

  printf("x: from to steps> ");
  if ( argc >= 4 ) {
    xfrom  = atof( argv[1] );
    xto    = atof( argv[2] );
    xsteps = atol( argv[3] );
    printf( "%lf %lf %d\n", xfrom, xto, xsteps );
  } else {
    scanf( "%lf %lf %d", &xfrom, &xto, &xsteps );
  }

  /* 微小区間幅の計算 */
  h = (xto-xfrom)/xsteps;
  /* 微小区間の開始点a の初期化 */
  a = xfrom;
  /* 積分値の初期化 */
  G = 0.0;
   
  for( xidx=1; xidx<=xsteps; xidx++ ) {
    /* 微小区間の終点b の計算 */
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    /* 分点の計算 */
    x1 = scale(-sqrt(3.0/5.0), a, b);
    x2 = scale(0, a, b);
    x3 = scale(sqrt(3.0/5.0), a, b);
    /* 関数値の計算 */
    f1 = fun(x1);
    f2 = fun(x2);
    f3 = fun(x3);
    /* 積分計算 */
    G += (h/2)*((5*f1/9)+(8*f2/9)+(5*f3/9));
    /* 微小区間の終点a の更新 */
    a = b;
  }
  SUM = FUN(xto)-FUN(xfrom);
  diff = abst(G-SUM);
  diff_percent = diff/SUM*100;
  printf( "Answer: %20.14lf\n", G );
  printf( "error: \t%20.14lf (%.14lf%%)\n", diff, diff_percent);
  return 0;
}