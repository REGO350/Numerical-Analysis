#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE	(16)


/* 環境変数からのデータの読み込み */

double	matA[SIZE][SIZE], matB[SIZE][SIZE];
int	n, verbose;

void printhelp( void )
{
  printf( "\nDemonstration program for Matrix Multiplication\n" );
  printf( "\t(c) Copyright M.Takata, 2011/05/16\n\n" );
  printf( "Syntax:\n" );
  printf( "    xmp06d [options] datafile ...\n" );
  printf( "Options:\n" );
  printf( "\t-h: shows help message, as you see now.\n" );
  printf( "\t-v: designates verbose messages.\n" );
  printf( "\t-s size: designates size of matrices.\n" );
  printf( "\n" );
}


void M_M_Mult ( double a[SIZE][SIZE], double b[SIZE][SIZE], double c[SIZE][SIZE] )
{
  double s, tmp[SIZE][SIZE];
  int    i, j, k;

  for ( i=0; i<n; i++ ) {	/* 計算 */
    for ( j=0; j<n; j++ ) {
      s = 0.0;
      for ( k=0; k<n; k++ ) { s += a[i][k] * b[k][j]; }
      tmp[i][j] = s;
    }
  }
  for ( i=0; i<n; i++ ) {	/* コピー */
    for ( j=0; j<n; j++ ) { c[i][j] = tmp[i][j]; }
  }
}

void M_Read ( FILE *fp, double a[SIZE][SIZE] )
{
  int	i, j;

  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) {
      fscanf( fp, "%lf", &(a[i][j]) );
      if (verbose) printf( " %16lf", a[i][j] );
    }
    if (verbose) printf( "\n" );
  }
}

void M_Print ( double a[SIZE][SIZE] )
{
  int	i, j;

  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) {
      if (verbose) {
	      printf( " %16lf", a[i][j] );
      }	
    }
    if (verbose) { printf( "\n" ); }
  }
  if (verbose) { printf( "\n" ); }
}


int main( int argc, char **argv )
{
  int	i, j, k, c;
  char	ch, *ptr;
  FILE	*fp;
   
  n = 0;
  c = 1;
  verbose = 0;
   
  while (( ch = getopt(argc,argv,"vhs:")) != -1 ) {
    if ( ch == 'v' ) { verbose = 1; }
    if ( ch == 'h' ) { printhelp(); return 1; }
    if ( ch == 's' ) { sscanf( optarg, "%d", &n ); }
  }

  if ( n == 0 ) {		/* サイズ入力 */
    if ( ptr = getenv("MATRIXSIZE") ) {
      n = atoi( ptr );
    }
  }
  if ( n == 0 ) {
    printf( "Size: " );
    scanf( "%d", &n );
  }
  if ( n > SIZE ) {		/* エラー処理 */
    printf( "error: Size should be less than or equal to %d.\n", SIZE );
    return 1;
  }


  if ( optind < argc ) {

				/* 最初の行列データファイルのオープン */
    if ( ( fp = fopen( argv[optind], "r" ) ) == NULL ) {
      printf( "error: File open error: %s\n", argv[optind] );
      return 1;
    }

    if (verbose) printf( "mat %d:\n", c );
    M_Read( fp, matA );	/* 最初の行列の読み込み */
    fclose( fp );
   
    optind++;
    c++;
  } else {
    printf( "missing data file name!\n" );
    return 1;
  }


  while ( optind < argc ) {

				/*後続の行列データファイルのオープン */
    if ( ( fp = fopen( argv[optind], "r" ) ) == NULL ) {
      printf( "error: File open error: %s\n", argv[optind] );
      return 1;
    }
   
    if (verbose) printf( "mat %d:\n", c );
    M_Read( fp,  matB );	/* 後続の行列の読み込み */
    fclose( fp );

    optind++;
    c++;
   
    if (verbose) printf( "product:\n" );

    M_M_Mult( matA, matB, matA );

    if (optind == argc) { verbose++; }
    M_Print( matA );
  }

  return 0;
}
