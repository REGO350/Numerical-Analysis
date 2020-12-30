#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define SIZE	(8)

/* N-1 次多項式 最小自乗近似フロントエンド */

int main( int argc, char **argv )
{
  double c, cy, x, y, xx[(2*SIZE-1)], xy[(2*SIZE-1)];
  int	 n, i, j, k;
  char   copyright[] = "Written by M.Takata: 2011/05/24\n";
  int    ch, verbose=0, query=1;
  
  verbose = 0;
  while (( ch = getopt(argc,argv,"vhn:")) != -1 ) {
    if ( ch == 'v' ) verbose = 1;
    if ( ch == 'h' ) {
      fprintf( stderr, "Options:\n" );
      fprintf( stderr, "\t-v: dumps intermediate results.\n" );
      fprintf( stderr, "\t-h: shows help message, as you see now.\n" );
      fprintf( stderr, "\t-n N: shows # of coeff. of a polynomial fitted.\n" );
      fprintf( stderr, "\n" );
      return 1;
    }
    if ( ch == 'n' ) {
      query = 0; sscanf( optarg, "%d", &n );
    }
  }


  if ( query == 1 ) {		/* 係数の数入力 */
    fprintf( stderr, "#coeff: " );
    scanf( "%d", &n );
  }
  if ( n > SIZE ) {		/* エラー処理 */
    fprintf( stderr, "error: #coeff. should be less than or equal to %d.\n", SIZE );
    return 1;
  }


  for (i=0; i<(2*SIZE-1); i++) { xx[i] = xy[i] = 0; }


				/* データ入力 */
  while ( scanf( "%lf %lf", &x, &y ) != EOF ) {
    c = 1;	cy = y;
    for (i=0; i<n; i++) {
      xx[i] += c;	c  *= x;
      xy[i] += cy;	cy *= x;
    }
    for (i=n; i<2*n-1; i++) {
      xx[i] += c;	c  *= x;
    }
  }


				/* 計算結果出力 */
  printf(" %d\n", n);
  for (i=0; i<n; i++) {
    for (j=i; j<i+n; j++) {
      printf(" %.12le", xx[j] );
    }
    printf("   %.12le\n", xy[i] );    
  }
  printf("\n");

}
