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
#ifndef MAX_ITER
#define MAX_ITER	(200)
#endif

double	matA[SIZE][SIZE], vecB[SIZE];
double	vecX[SIZE], vecX_tmp[SIZE];
double	tmpA[SIZE][SIZE], tmpB[SIZE];
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
  int		i, j, k, process_continue, iter, dig, map;
  double 	C, Sum, prec, p;
  double    elapsed_time;
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
	      prec /= 10.0;
      }
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

  /* 初期値代入 */
  for (i=0; i<n; i++) {
    vecX[i] = C;		
  }

  /* 問題の読み込み */
  Simal_Read( matA, vecB );	

  /* matA，vecB の表示 */
  if (verbose) {
    printf("\n### Input matA and matB\n");
    Simal_Write( matA, vecB );		/* 清書 */
  }

  /*誤差計算用*/
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      tmpA[i][j] = matA[i][j];
    }
    tmpB[i] = vecB[i];
  }

  int band_width1[n], band_width2[n];
  for(k=0;k<n;k++){
    band_width1[k] = 0;
    band_width2[k] = 0;
  }
  for(k=0;k<n;k++){
    for(j=n-1;j>=k;j--){
      if(matA[k][j]==0) band_width2[k]++;
      else break;
    }
    for(j=0;j<k;j++){
      if(matA[k][j]==0) band_width1[k]++;
      else break;
    }
  }

  /* 計算時間計測開始 */
  times( &tfrom );			

  /* 計算開始 */
  printf("\n### Start calculation ...\n");
  unsigned int prod_sum = 0;
  iter = 0;
  process_continue = 1;
  while ( process_continue && (iter<MAX_ITER) ) {
    if (!map) {
      printf( "%03d: ", iter );
      V_Write( vecX );			/* 暫定解の書き出し */
    }

    /* Jacobi法の計算（仮の解 vecX_tmp の導出） */
    for (j=0; j<n; j++) {       /* x_1 から x_n までの計算 */
      /* Implement here: A */
      C = matA[j][j];
      Sum = vecB[j]/C;
      for(k=0+band_width1[j];k<j;k++){
        Sum += -matA[j][k]/C * vecX[k];
        prod_sum++;
      }
      for(k=j+1;k<n-band_width2[j];k++){
        Sum += -matA[j][k]/C * vecX[k];
        prod_sum++;
      }
      vecX_tmp[j] = Sum;
    }

    /* 繰り返し回数 iter の更新 */
    iter++;

    if (map) {
      printf( "%03d: ", iter );
    }

    /* 収束判定処理 */
    process_continue = 0;
    for (i=0; i<n; i++) {		/* 収束状況の確認 */
      p = 999;
      if ( vecX_tmp[i]!=0 && (p=fabs((vecX_tmp[i]-vecX[i])/vecX_tmp[i])) > prec ) {
	    process_continue = 1; 
      }

      if (map) {			/* 有効桁数マップの作成 */
        dig = (long)( -log(p)/log(10.0)+0.5 );
        if (dig > 9) { dig = 9; }
        if (dig < 0) { dig = 0; }
        printf( "%c ", (dig<=0) ? '.' : '0'+dig );
        if (i%100 == 99) {
          printf("\n     ");
        }
      }
      /* 仮の解 vecX_tmp を 解 vecX へコピー */
      vecX[i] = vecX_tmp[i];
    }

    if (map) {
      printf("\n");
    }
  }

  /* 計算時間計測終了 */
  times( &tto );			

  /* 最終解の書き出し */
  printf("\n### Final soluation:\n");
  printf( "%03d: ", iter );
  V_Write( vecX );		

  /*誤差計算*/
  M_V_Mult( tmpA, vecX, vecX ); 
  int nn = 0; 
  double error = 0.0;
  for(i=0;i<n;i++){
    if(tmpB[i]!=0){
      error += fabs(vecX[i] - tmpB[i])/tmpB[i]*100;
    }else{
      nn++;
    }
  }
  error /= n-nn;
  printf( "\n### Mean Error: %.10lf%%\n", error );	

  /* 計算時間表示 */
  printf("\n### prod_sum: %dtimes\n", prod_sum);
  elapsed_time =  (double)(tto.tms_utime-tfrom.tms_utime)/sysconf(_SC_CLK_TCK);

  printf("\n### User cpu time: %.12lf [sec]\n\n", elapsed_time);

  return 0;
}
