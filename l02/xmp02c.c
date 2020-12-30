#include <stdio.h>

int main (void) {
  float          data4, sum4;	/* 32 bit */
  double         data8, sum8;	/* 64 bit */
  long double    data16, sum16;	/* 80 bit */
  int            o;

  printf( "Order> " );		/* 桁数 */
  scanf( "%d", &o );

  data16 = (long double) 1.0;
  while( o-- ) {		/* o 回繰り返すときの定石 */
    data16 *= (long double) 10.0;      /* 10 の o 乗 */
  }

  data4  = ((float)  1.0)      / data16;
  data8  = ((double) 1.0)      / data16;
  data16 = ((long double) 1.0) / data16;

  sum4  = (float) 1.0;
  sum8  = (double) 1.0;
  sum16 = (long double) 1.0;

  sum4  += data4;
  sum8  += data8;
  sum16 += data16;

  printf( "Ans4:  %e,  Err4:  %8.1e\n",   sum4 - 1, (sum4 - 1) - data4 );
  printf( "Ans8:  %le,  Err8:  %8.1le\n", sum8 - 1, (sum8 - 1) - data8 );
  printf( "Ans16: %Le,  Err16: %8.1Le\n", sum16 - 1, (sum16 - 1) - data16 );

  return 0;
}
