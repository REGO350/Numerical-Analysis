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

  /* (2) */
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      s=0.0;
      for(k=0;k<n;k++)
        s+=a[i][k]*b[k][j];
      c[i][j]=s;
    }
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

  /* 行列の読み込み */
  printf( "matA:\n" );	  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { scanf( "%lf", &(matA[i][j]) ); }
    printf( "\n" );
  }

  /* 行列の読み込み */
  printf( "matB:\n" );	
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { scanf( "%lf", &(matB[i][j]) ); }
    printf( "\n" );
  }
 
  /* 行列同士の掛け算 */  
  M_M_Mult( matA, matB, matC );

  /* 結果出力 */
  printf( "matC = matA x matB:\n" );
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { printf( "%16lf\t", matC[i][j] ); }
    printf( "\n" );
  }
  printf( "\n" );

  return 0;
}
