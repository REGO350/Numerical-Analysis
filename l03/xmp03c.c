#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define min(x,y) (x<y?x:y)
#define	EPSILON	(1e-12)
#define M_PI 3.14159265358979323846

int verbose=0;					/* 饒舌モードスイッチ */

double func( double x )				/* 解きたい方程式 */
{
  return pow(x,3)-6*pow(x,2)+3*x+16;
}

void iterate( double x0, double x1, double y0, double y1, int n )	/* 再帰的に呼び出される関数 */
{
  double  x, y;

  x = (x0 * y1 - x1 * y0) / (y1 - y0);
  y = func(x);
  if (n++ > 100) {				/* 暴走よけ */
    printf( "Too Many Recursions\n" );
    return;
  }

  if (verbose) {				/* 饒舌モード */
    printf( "%03d> %18.14lf %18.14lf %18.14lf %16.1le %10.1le\n",
	    n, x0, x, x1, min(fabs(x-x0),fabs(x-x1))/fabs(x), y );
  }

  if (y == 0) {
    printf( "Ans(%03d): %20.14lf %16.1le\n", n, x, y );
  } else if (fabs(x-x0) < fabs(x) * 1e-12) {	/* 答えの精度の制御 */
    printf( "Ans(%03d): %20.14lf %16.1le\n", n, x, y );
  } else if (fabs(x-x1) < fabs(x) * 1e-12) {	/* 答えの精度の制御 */
    printf( "Ans(%03d): %20.14lf %16.1le\n", n, x, y );
  } else if (y0 * y < 0) {
    iterate( x0, x, y0, y, n );
  } else {
    iterate( x, x1, y, y1, n );
  }
}

int main (int argc, char **argv) {
  double  x0, x, y0, y;
  double  xfrom, xto;
  int	  xsteps, xidx;
  char    ch;
  
  while (( ch = getopt(argc,argv,"v")) != -1 ) {	/* 実行時オプション */
    if ( ch == 'v' ) { verbose = 1; }			/* -v: 饒舌になる */
  }

  printf("x: from to steps> ");
  if ( argc >= optind+3 ) {		/* コマンド行に十分な数のデータが存在するかテスト */
    xfrom  = atof( argv[optind+0] );		/* 最初の文字列を double に変換 */
    xto    = atof( argv[optind+1] );		/* 二番目の文字列を double に変換 */
    xsteps = atol( argv[optind+2] );		/* 三番目の文字列を long int に変換 */
    printf( "%lg %lg %d\n", xfrom,  xto,  xsteps );	/* 確認出力 */
  } else {
    scanf(  "%lf %lf %d",  &xfrom, &xto, &xsteps );
  }

  x0 = xfrom;
  if ((y0 = func(x0)) == 0) {
    printf( "Ans(%03d): %20.14lf %16.6le\n", 0, x0, y0 );
  }

  for( xidx=1; xidx<=xsteps; xidx++ ) {
    x = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    y = func(x);
    if (y == 0) {
      printf( "Ans(%03d): %20.14lf %16.6le\n", 0, x, y );
    } else if (y0 * y < 0) {
      // puts("****");
      iterate(x0, x, y0, y, 0);
    }
    x0 = x; y0 = y;
  }

  return 0;
}
