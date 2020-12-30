#include <stdio.h>
#include <stdlib.h>

#define SIZE	(8)

double	matA[SIZE][SIZE];
double	vecA[SIZE], vecB[SIZE];
int	n;

/* 行列とベクトルとの掛け算 */

void M_V_Mult ( double a[SIZE][SIZE], double b[SIZE], double c[SIZE] )
{
  double sum, tmp[SIZE];
  int    i, j, k;

  for ( i=0; i<n; i++ ) {	/* 計算 */
    sum = 0.0;
    for ( k=0; k<n; k++ ) { sum += a[i][k] * b[k]; }
    tmp[i] = sum;
  }

  for ( i=0; i<n; i++ ) {	/* コピー */
    c[i] = tmp[i];
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
   
  printf( "vecA:\n" );		/* ベクトルの読み込み */
  for ( i=0; i<n; i++ ) { scanf( "%lf", &(vecA[i]) ); }

  M_V_Mult( matA, vecA, vecB );

  printf( "vecB = matA x vecA:\n" );	/* 結果出力 */
  for ( i=0; i<n; i++ ) { printf( "%16lf\n", vecB[i] ); }
  printf( "\n" );

  return 0;
}
