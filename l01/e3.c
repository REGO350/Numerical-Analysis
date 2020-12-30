#include <stdio.h>
#include <math.h>

int main (void) {
  double data, sum, sum2, mean, sd;
  int    n;

  n = 0;
  sum = 0;
  sum2 = 0;

  while ( scanf( "%lf", &data ) != EOF ) {	/* ファイルの姜りまでを乖ごとに借妄する疯まり矢剁 */
    n++;					/* n の面咳を 1 笼やす */
    sum += data;
    sum2 += data * data;
  }

  if ( n > 1 ) {				/* 2 乖笆惧あったとき */
    mean = sum / n;
    sd = sqrt( (sum2 - sum * mean) / (n - 1) );
    printf( "N: %d,  Mean: %f,  SD: %f\n", n, mean, sd );
  } else if ( n ) {				/* 1 乖だけだったとき */
    printf( "N: %d,  Mean: %f\n", n, sum );
  } else {					/* 0 乖だったとき */
    printf( "NO DATA!\n");
  }

  return 0;
}
