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
  /* (1) */
  for(i=0;i<n;i++){
    sum=0.0;
    for(j=0;j<n;j++)
      sum+=a[i][j]*b[j];
    c[i] = sum;  
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
  printf( "matA:\n" );
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) { scanf( "%lf", &(matA[i][j]) ); }
    printf( "\n" );
  }

  /* ベクトルの読み込み */
  printf( "vecA:\n" );		
  for ( i=0; i<n; i++ ) { scanf( "%lf", &(vecA[i]) ); }

  /* 行列とベクトルとの掛け算 */
  M_V_Mult( matA, vecA, vecB );

  /* 結果出力 */
  printf( "vecB = matA x vecA:\n" );	 
  for ( i=0; i<n; i++ ) { 
    printf( "%16lf\n", vecB[i] ); 
  }

  printf( "\n" );

  return 0;
}
