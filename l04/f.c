#include <stdio.h>
#include <stdlib.h>

/* Lagrange Four Point Interpolation */
        /*    Equally Spaced    */

int main ( int argc, char **argv ) {
  double  f_1, f0, f1, f2, p, f;

  printf("f-1 = f(-1)> ");
  scanf( "%lf", &f_1 );
  printf("f0 = f(0)> ");
  scanf( "%lf", &f0 );
  printf("f1 = f(1)> ");
  scanf( "%lf", &f1 );
  printf("f2 = f(2)> ");
  scanf( "%lf", &f2 );

  printf( "p for f(p)> " );
  while ( scanf( "%lf", &p ) != EOF ) {		/* ファイルの終りまでを行ごとに処理する決まり文句 */
    f = -p*(p-1)*(p-2)/6*f_1 + (p+1)*(p-1)*(p-2)/2*f0 - (p+1)*p*(p-2)/2*f1 + (p+1)*p*(p-1)/6*f2;
    printf( "f(%lf) = %lf\n", p, f );
    printf( "p for f(p)> " );
  }

  printf( "\n" );
  return 0;
}
