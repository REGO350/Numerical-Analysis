#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>
#include <limits.h>

#ifndef SIZE
#define SIZE	(1024)
#endif
#ifndef LIMIT
#define LIMIT	(200)
#endif


double	matA[SIZE][SIZE], vecB[SIZE], vecX[SIZE], vecT[SIZE], tmpA[SIZE][SIZE], tmpB[SIZE];
int	n, verbose;

void Simal_Read ( double a[SIZE][SIZE], double b[SIZE] )	/* 連立方程式の読み込み */
{
  int	i, j;
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) {
      scanf( "%lf", &(a[i][j]) );
    }
    scanf( "%lf", &(b[i]) );
  }
}

void Simal_Write ( double a[SIZE][SIZE], double b[SIZE] )	/* 連立方程式の書き出し */
{
  int	i, j;
  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) {
      printf( "%11.3le ", a[i][j] );
    }
    printf( "  %11.3le\n", b[i] );
  }
}

void V_Write ( double a[SIZE] )		       	/* ベクトルの書き出し */
{
  int i;
  for (i=0; i<n; i++) {
    printf( " %15.8le", a[i] );
  }
  printf( "\n" );
}

void M_V_Mult ( double a[SIZE][SIZE], double b[SIZE], double c[SIZE] )
{
  double sum, tmp[SIZE];
  int    i, j, k;

  for ( i=0; i<n; i++ ) {	
    sum = 0.0;
    for ( k=0; k<n; k++ ) { sum += a[i][k] * b[k]; }
    tmp[i] = sum;
  }

  for ( i=0; i<n; i++ ) {	
    c[i] = tmp[i];
  }
}

int main( int argc, char **argv )
{
  int		i, j, k, cont, cc, dig, map, nn;
  double 	C, Sum, prec, p, error=0.0;
  struct tms	tfrom, tto;
  char		ch, *ptr;
   
  n = 0;
  verbose = 0;
  map = 0;
  C = 0;
  prec = 1e-5;
   
  while (( ch = getopt(argc,argv,"vms:i:p:")) != -1 ) {
    if ( ch == 'v' ) { verbose = 1; }		/* おしゃべり */
    if ( ch == 'm' ) { map = 1; }		/* マップ表示選択 */
    if ( ch == 's' ) { n = atoi( optarg ); }	/* 連立元数 Size */
    if ( ch == 'i' ) { C = atof( optarg ); }	/* 初期値 */
    if ( ch == 'p' ) {				/* 要求精度 (桁数) */
      j = atoi( optarg );
      prec = 1.0;
      for (i=0; i<j; i++) {
	      prec *= 10.0;
      }
      prec = 1.0 / prec;
    }
  }

  if ( n == 0 ) {
    printf( "Size: " );
    scanf( "%d", &n );
    printf( "\n" );
  }
  if ( n > SIZE ) {			/* エラー処理 */
    printf( "error: Size should be less than or equal to %d.\n", SIZE );
    return 1;
  }

  for (i=0; i<n; i++) {
    vecX[i] = C;			/* 初期値代入 */
  }

  Simal_Read( matA, vecB );		/* 問題の読み込み */
  if (verbose) {
    Simal_Write( matA, vecB );		/* 清書 */
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      tmpA[i][j] = matA[i][j];
    }
    tmpB[i] = vecB[i];
  }

  for (j=0; j<n; j++) {			/* 係数マトリクスの下準備 */
    C = matA[j][j];
    for (k=0; k<n; k++) {
      if (j != k) {
	      matA[j][k] = -matA[j][k]/C;
      }
    }
    vecB[j] = vecB[j]/C;
  }

  times( &tfrom );			/* 計算時間計測開始 */

  cc = 0;
  cont = 1;
  while ( cont && (cc<LIMIT) ) {
    if (!map) {
      printf( "%03d: ", cc );
      V_Write( vecX );			/* 暫定解の書き出し */
    }

    for (j=0; j<n; j++) {
      Sum = vecB[j];
      for (k=0; k<n; k++) {
        if (j != k) {
          Sum += matA[j][k] * vecX[k];	/* 積和計算 */
        }
      }
      vecT[j] = Sum;
    }
    cc++;

    if (map) {
      printf( "%03d: ", cc );
    }
    cont = 0;
    for (i=0; i<n; i++) {		/* 収束状況の確認 */
      p = 999;
      if ( vecT[i]!=0 && (p=fabs((vecT[i]-vecX[i])/vecT[i])) > prec ) {
	      cont = 1; 
      }
      if (map) {			/* 有効桁数マップの作成 */
	      dig = (long)( -log(p)/log(10.0)+0.5 );
	      if (dig > 35) { dig = 35; }
	      if (dig < 0) { dig = 0; }
	      printf( "%c", (dig<=0) ? '.' : ((dig<10)?'0'+dig:'A'+dig-10) );
	      if (i%100 == 99) { printf("\n     "); }
      }
      vecX[i] = vecT[i];
    }
    if (map) { printf("\n"); }
  }

  times( &tto );			/* 計算時間計測終了 */
  printf( "%03d: ", cc );
  V_Write( vecX );			/* 最終解の書き出し */

  M_V_Mult( tmpA, vecX, vecX ); /*誤差計算*/
  nn=0;
  for(i=0;i<n;i++){
    if(tmpB[i]!=0){
      error += fabs(vecX[i] - tmpB[i])/tmpB[i]*100;
    }else{
      nn++;
    }
  }
  error /= n-nn;
  printf( "\nMean Error:%.10lf%%\n", error );

  printf( "    user cpu time: %.2lf [sec]\n\n",(double)(tto.tms_utime-tfrom.tms_utime)/sysconf(_SC_CLK_TCK) );
  return 0;
}
