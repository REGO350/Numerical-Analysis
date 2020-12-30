#include <stdio.h>
#include <stdlib.h>

/* Linear Lagrange Interpolation */
        /*    Equally Spaced    */

int main ( int argc, char **argv ) {
  double  f0, f1, p, f;

  printf("f0 = f(0)> ");
  scanf( "%lf", &f0 );
  printf("f1 = f(1)> ");
  scanf( "%lf", &f1 );

  printf( "p for f(p)> " );
  while ( scanf( "%lf", &p ) != EOF ) {		/* ファイルの終りまでを行ごとに処理する決まり文句 */
    f = (1-p)*f0 + p*f1;
    printf( "f(%lf) = %lf\n", p, f );
    printf( "p for f(p)> " );
  }

  printf( "\n" );
  return 0;
}
