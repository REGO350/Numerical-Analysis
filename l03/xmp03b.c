#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define	EPSILON	(1e-12)				/* 欲しい精度 */

int verbose=0;					/* 饒舌モードスイッチ */

double func( double x )				/* 解きたい方程式 */
{
  return sin(x) - 0.2;
  // return pow(x,2) - 2*x;
}


double diff( double x )				/* 解きたい方程式の導関数 */
{
  return cos(x);
}


void iterate( double x0, int n )		/* 再帰的に呼び出される関数 */
{
  double  y0, x, y, delta;

  y0 = func(x0);
  x = x0 + ( delta = - y0 / diff( x0 ) );	/* 接線の x 切片を求める */
  if (n++ > 100) {				/* 暴走よけ */
    printf( "Too Many Recursions\n" );
    return;
  }

  y = func(x);

  if (verbose) {				/* 饒舌モード */
    printf( "%03d> %20.14lf %16.1le %10.1le\n", n, x, delta, y );
  }

  if (y == 0) {
    printf( "Ans(%03d): %20.14lf %16.1le %10.1le %10.1le\n",
	    n, x, func(x*(1-EPSILON)), y, func(x*(1+EPSILON)) );
  } else if (fabs(delta) < fabs(x)*EPSILON) {	/* 答えの精度の制御 */
    printf( "Ans(%03d): %20.14lf %16.1le %10.1le %10.1le\n",
	    n, x, func(x*(1-EPSILON)), y, func(x*(1+EPSILON)) );
  } else {
    iterate( x, n );
  }
}


int main (int argc, char **argv) {
  double  x, y;
  double  xfrom, xto;
  int	  xsteps, xidx;
  char    ch;

  while (( ch = getopt(argc,argv,"v")) != -1 ) {	/* 実行時オプション */
    if ( ch == 'v' ) { verbose = 1; }			/* -v: 饒舌になる */
  }
  
  printf("x: from to steps> ");
  scanf( "%lf %lf %d", &xfrom, &xto, &xsteps );
  
  for( xidx=0; xidx<=xsteps; xidx++ ) {
    x = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    if ((y = func(x)) == 0) {
      printf( "Ans(%03d): %20.14lf %16.5le %12.5le %12.5le\n",
	      0, x, func(x*(1-EPSILON)), y, func(x*(1+EPSILON)) );
    } else {
      if (verbose) {
	printf( "%03d> %20.14lf\n", 0, x );
      }
      iterate( x, 0 );
    }
  }

  return 0;
}
