#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* チェビシェフ 3 点公式 */

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
  double  x1, x2, x3, f1, f2, f3, Ch3;
  double  SUM, diff, diff_percent;
  double  a, b;

  printf("x: from to> ");
  if ( argc >= 3 ) {
    a = atof( argv[1] );
    b = atof( argv[2] );
    printf( "%lf %lf\n", a, b);
  } else {
    scanf( "%lf %lf", &a, &b);
  }

  /* 分点の計算 */
  x1 = scale(-1.0/sqrt(2.0), a, b);
  x2 = scale(0.0, a, b);
  x3 = scale(1.0/sqrt(2.0), a, b);
  /* 関数値の計算 */
  f1 = fun(x1);
  f2 = fun(x2);
  f3 = fun(x3);
  /* 積分計算 */
  Ch3 = (b-a)/2*(2*f1/3+2*f2/3+2*f3/3);
  SUM = FUN(b)-FUN(a);
  diff = abst(Ch3-SUM);
  diff_percent = diff/SUM*100;
  printf( "Answer: %20.14lf\n", Ch3 );
  printf( "error: \t%20.14lf (%.14lf%%)\n", diff, diff_percent);
  return 0;
}
