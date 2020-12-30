#include <stdio.h>
#include <unistd.h>

#define	EPSILON	(1e-4)	

double matA[SIZE][SIZE], matE[SIZE][SIZE], vecX[SIZE];

int main( int argc, char **argv ){
  int	  i, j, k;
  int   n, ch, verbose;
  

  verbose = 0;
  while (( ch = getopt(argc,argv,"vh")) != -1 ) {
    if ( ch == 'v' ) verbose = 1;
  }

  /* データ入力 */
  scanf( "%d", &n );
  double mat[n][n];

  for ( i=0; i<n; i++ ) {
    scanf("%lf", &(mat[i][i]));
    if(mat[i][i]<EPSILON){
      printf("(%d, %d) is very small\n", i, i);
    }
  }
  return 0; 
}
