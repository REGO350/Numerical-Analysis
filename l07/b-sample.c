#include <stdio.h>
#include <stdlib.h>

#define SIZE	(8)

double	matA[SIZE][SIZE], matB[SIZE][SIZE], matC[SIZE][SIZE];
int	n;

/* 行列同士の掛け算 */

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


int main ( void )
{
  int    i, j;

  printf( "Size> " );		/* サイズ入力 */
  scanf( "%d", &n );
  if ( n > SIZE ) {		/* エラー処理 */
    printf( "error: Size should be less than or equal to %d.\n", SIZE );
    return 1;
  }
   
  printf( "matA:\n" );		/* 行列の読み込み */
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { scanf( "%lf", &(matA[i][j]) ); }
    printf( "\n" );
  }
  
  printf( "matB:\n" );		/* 行列の読み込み */
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { scanf( "%lf", &(matB[i][j]) ); }
    printf( "\n" );
  }
   
  M_M_Mult( matA, matB, matC );

  printf( "matC = matA x matB:\n" );	/* 結果出力 */
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { printf( "%16lf\t", matC[i][j] ); }
    printf( "\n" );
  }
  printf( "\n" );

  return 0;
}
