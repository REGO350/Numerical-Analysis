#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define SIZE	(8)

/* n-1 次多項式補間フロントエンド */

int main( int argc, char **argv )
{
  double c, x, y;
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


  if ( query == 1 ) {		/* 次数入力 */
    fprintf( stderr, "#coeff: " );
    scanf( "%d", &n );
  }
  if ( n > SIZE ) {		/* エラー処理 */
    fprintf( stderr, "error: ＃coeff. should be less than or equal to %d.\n", SIZE );
    return 1;
  }


  printf(" %d\n", n);


  /* n個のデータ入力 および 表示 */
  for (j=0; j<n; j++) { 
    /* A */
    scanf("%lf %lf", &x, &y);
    for(i=0;i<n;i++)
      printf("  %.5le", pow(x,i));
    printf("  %.5le\n", y);
  }

  printf("\n");



}
