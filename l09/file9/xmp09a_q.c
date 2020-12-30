#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define SIZE	(8)

/* m 次多項式 最小自乗近似フロントエンド */

int main( int argc, char **argv )
{
  double c, cy, x, y, xx[(2*SIZE-1)], xy[(2*SIZE-1)];
  int	 m, i, j, k;
  char   copyright[] = "Written by M.Takata: 2011/05/24, and modified by H.Kasai on July 18, 2018.\n";
  int    ch, verbose=0, query=1;
  
  verbose = 0;
  while (( ch = getopt(argc,argv,"vhm:")) != -1 ) {
    if ( ch == 'v' ) verbose = 1;
    if ( ch == 'h' ) {
      fprintf( stderr, "Options:\n" );
      fprintf( stderr, "\t-v: dumps intermediate results.\n" );
      fprintf( stderr, "\t-h: shows help message, as you see now.\n" );
      fprintf( stderr, "\t-m N: shows # of coeff. of a polynomial fitted.\n" );
      fprintf( stderr, "\n" );
      return 1;
    }
    if ( ch == 'm' ) {
      query = 0; sscanf( optarg, "%d", &m );
    }
  }


  if ( query == 1 ) {		/* 係数の数入力 */
    fprintf( stderr, "#coeff: " );
    scanf( "%d", &m );
  }
  if ( m > SIZE ) {		/* エラー処理 */
    fprintf( stderr, "error: ＃coeff. should be less than or equal to %d.\n", SIZE );
    return 1;
  }


  /* xx配列の初期化: B */

  /* xy配列の初期化: C */


  /* 不定数個のデータ入力と表示 */
  while ( scanf( "%lf %lf", &x, &y ) != EOF ) {
    c = 1;	cy = y;

    /* xx 配列の計算: D */

    /* xy 配列の計算: E */
  }


  /* 計算結果出力 */
  printf(" %d\n", m);
  for (i=0; i<m; i++) {
    for (j=i; j<i+m; j++) {
      printf(" %.12le", xx[j] );
    }
    printf("   %.12le\n", xy[i] );    
  }
  printf("\n");

}
