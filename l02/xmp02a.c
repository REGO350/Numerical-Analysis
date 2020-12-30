#include <stdio.h>

int main (void) {
  float          data4, sum4;	/* 32 bit */
  double         data8, sum8;	/* 64 bit */
  int            o;		/* 32 bit */
  long long int  n, c;		/* 64 bit */

  printf( "Order> " );		/* 桁数 */
  scanf( "%d", &o );
  n = 1;
  for( c=0; c<o; c++ ) {	/* o 回繰り返すときの定石 */
    n *= 10;			/* 10 の o 乗 */
  }

  data8 = ((double) 1.0) / n;
  data4 = (float) data8;
  sum4 = 0;
  sum8 = 0;

  for( c=0; c<n; c++ ) {	/* n 回繰り返すときの定石 */
    sum4 += data4;
    sum8 += data8;
  }

  printf( "Ans4: %f,  Err4: %8.1e\n",   sum4, sum4 - 1 );
  printf( "Ans8: %lf,  Err8: %8.1le\n", sum8, sum8 - 1 );

  return 0;
}


