#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main (void) {
  float    a4, b4, c4, d4, x4, y4;
  double   a8, b8, c8, d8, x8, y8;

  float          data4, sum4;
  double         data8, sum8;
  int            o;
  long long int  n, c;

  printf( "a, b, c> " );
  scanf( "%lf %lf %lf", &a8, &b8, &c8 );
  a4 = a8;
  b4 = b8;
  c4 = c8;

  d8 = b8 * b8 - 4.0 * a8 * c8;
  if ( d8 < 0 ) {
    printf( "No root!\n" );
    return -1;
  }
  
  d8 = sqrt( d8 );
  x8 = ( - b8 + d8 ) / ( 2.0 * a8 );
  y8 = ( 2.0 * c8 ) / ( - b8 + d8 );
  d4 = (float) sqrt( b4 * b4 - 4.0 * a4 * c4 );
  x4 = ( - b4 + d4 ) / ( 2.0 * a4 );
  y4 = ( 2.0 * c4 ) / ( - b4 + d4 );
  
  printf( "Ans8: %.8le(%8.1le),  %.8le(%8.1le)\n",
	  x8, (a8 * x8 + b8) * x8 + c8, y8, (a8 * y8 + b8) * y8 + c8 );

  x8 = x4;
  y8 = y4;
  
  printf( "Ans4: %.8le(%8.1le),  %.8le(%8.1le)\n",
	  x8, (a8 * x8 + b8) * x8 + c8, y8, (a8 * y8 + b8) * y8 + c8 );

  return 0;
}
