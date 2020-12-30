#include <stdio.h>
#include <unistd.h>

#ifndef  SIZE
#define  SIZE	(16)
#endif

#define	EPSILON	(1e-4)	

double matA[SIZE][SIZE], matE[SIZE][SIZE], vecX[SIZE], tmpA[SIZE][SIZE], tmpX[SIZE];
int n;

void dump ( int n )
{
  int    j, k;
  for ( k=0; k<n; k++ ){
    printf( "\n" );
    for ( j=0; j<n; j++ ) printf( " %10.3le", matA[k][j] );
    printf(                    "    %10.3le   ", vecX[k] );
    for ( j=0; j<n; j++ ) printf( " %10.3le", matE[k][j] );
  }
  printf( "\n" );
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
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
  double C, D, tmp, max;
  int	  i, j, k, max_j;
  char   copyright[] = "Written by M.Takata: 1999/01/20\n";
  int    ch, verbose;
  double error=0.0;
  
  verbose = 0;
  while (( ch = getopt(argc,argv,"vh")) != -1 ) {
    if ( ch == 'v' ) verbose = 1;
    if ( ch == 'h' ) {
      printf( "Options:\n" );
      printf( "\t-v: dumps intermediate results.\n" );
      printf( "\t-h: shows help message, as you see now.\n" );
      printf( "\n" );
      return 1;
    }
  }


  /* データ入力 */
  scanf( "%d", &n );
  if ( n > SIZE ) {
    printf("N should be less than or equal to %d.\n", SIZE);
    return 1;
  }

  for ( i=0; i<n; i++ ) {
    for ( j=0; j<n; j++ ) {
      scanf( "%lf", &(matA[i][j]) ); 
      if(i==j){
        if(matA[i][i]==0.0){
          printf("(%d, %d) is 0\n", i, i);
        }else if(abst(matA[i][i])<EPSILON){
          printf("(%d, %d) is very small\n", i, i);
        }
      }
    }
    scanf( "%lf", &(vecX[i]) );
  }

  printf("Inputs:\n");
  
  for ( i=0; i<n; i++ ){
    for ( j=0; j<n; j++ ){
      printf( " %12.5le", matA[i][j] ); }
    printf( "  |  %12.5le\n", vecX[i] );
  }

  /* 単位行列の設定 */
  for ( i=0; i<n; i++ ){
    for ( j=0; j<n; j++ ){ matE[i][j] = 0.0; }
    matE[i][i] = 1.0;
  }


  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      tmpA[i][j] = matA[i][j];
    }
    tmpX[i] = vecX[i];
  }


  /* Gauss-Jordan 法 */
  if ( verbose ) dump( n );

  for ( i=0; i<n; i++ ){

    //i列のi行〜n行の中で最大の値を持つ行max_jを探す。
    max = 0; max_j = i;
    for(j=i;j<n;j++){
      if(abst(matA[j][i])>max){
        max = abst(matA[j][i]);
        max_j = j;
      }
    }

    //行の入れ替え
    for(j=0;j<n;j++){
      tmp = matA[i][j];
      matA[i][j] = matA[max_j][j];
      matA[max_j][j] = tmp;
    }
    tmp = vecX[i];
    vecX[i] = vecX[max_j];
    vecX[max_j]= tmp;
    for(j=0;j<n;j++){
      tmp = matE[i][j];
      matE[i][j] = matE[max_j][j];
      matE[max_j][j] = tmp;
    }

    if ( verbose ) dump( n );

    //pivot
    C = matA[i][i]; 

    if ( C == 0 ) {
      printf( "Ill conditioned matrix, A[%d][%d] = %le\n\n", i, i, C );
      return 1;
    }

    /********************************************/
    /**            i 列目前半の処理 (A)        **/
    /********************************************/
    for(j=0;j<n;j++){
      matE[i][j] /= C;
      matA[i][j] /= C;
    }
    vecX[i] /= C;

    if ( verbose ) dump( n );

    for ( k=0; k<n; k++ ){
      if ( i != k ){
        D = matA[k][i];
        /********************************************/
	      /**            i 列目後半の処理 (B)        **/
	      /********************************************/
        for(j=0;j<n;j++){
          matA[k][j] -= D*matA[i][j];
          matE[k][j] -= D*matE[i][j];
        }
        vecX[k] -= D*vecX[i];
      }
    }

    if ( verbose ) dump( n );
    puts("############");
  }

  /* 計算結果出力 */
  printf( "\nResults:\n" );
  for ( i=0; i<n; i++ ) printf( " %12.5le", vecX[i] );
  printf( "\nInverse:\n" );
  for ( i=0; i<n; i++ ){
    for ( j=0; j<n; j++ ) printf( " %12.5le", matE[i][j] );
    printf("\n");
  }

  M_V_Mult( tmpA, vecX, vecX );
  for(i=0;i<n;i++){
    error += abst(vecX[i] - tmpX[i])/tmpX[i]*100;
  }
  error /= n;
  printf( "\nError:%.10lf%%\n", error );
}
