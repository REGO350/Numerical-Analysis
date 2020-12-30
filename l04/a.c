#include <stdio.h>
#include <stdlib.h>

/* Linear Lagrange Interpolation */

int main ( int argc, char **argv ) {
  double  x0, f0, x1, f1, x, f;

  printf("x0 f0> ");
  scanf( "%lf %lf", &x0, &f0 );
  printf("x1 f1> ");
  scanf( "%lf %lf", &x1, &f1 );

  printf( "x for f(x)> " );
  while ( scanf( "%lf", &x ) != EOF ) {		/* ファイルの終りまでを行ごとに処理する決まり文句 */
    f = (x-x1)/(x0-x1)*f0 + (x-x0)/(x1-x0)*f1;
    printf( "f(%lf) = %lf\n", x, f );
    printf( "x for f(x)> " );
  }

  printf( "\n" );
  return 0;
}
