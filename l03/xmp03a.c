#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int verbose=0;					/* 饒舌モードスイッチ */

double func( double x )				/* 解きたい方程式 */
{
  float a=0.36;
  double y=0.0;
  int b=29,i=0, N=30;
  for( ;i<N;i++){
    y+=pow(a,i)*cos(pow(b,i)*M_PI*x);
  }
  return y;
}

/*再帰的に呼び出される関数*/
void iterate( double a, double b, int n ) 
{
  double  ya, yb, c, yc;
   
  c = (a + b) / 2.0;				/* 中点を求める */
  ya = func(a);
  yb = func(b);
  yc = func(c);
  if (n++ > 100) {				/* 暴走よけ */
    printf( "Too Many Recursions\n" );
    return;
  }
  if (verbose) {				/* 饒舌モード */
    printf( "%03d> %18.14lf %18.14lf %18.14lf  %10.1le %10.1le\n",
	    n, a, c, b, fabs((a-b)/c), yc );
  }
  if (yc == 0) {
    printf( "Ans(%03d): %20.14lf %16.1le %10.1le\n", n, c, fabs((a-b)/c), yc );
  } else if (fabs(a-b) < fabs(c)*1e-12) {	/* 答えの精度の制御 */
    printf( "Ans(%03d): %20.14lf %16.1le %10.1le\n", n, c, fabs((a-b)/c), yc );
  } else if ( (a == c) || (c == b) ) {
    printf( "Ans(%03d): %20.14lf %16.1le %10.1le\n", n, c, fabs((a-b)/c), yc );
  } else if (ya * yc < 0) {
    iterate(a, c, n);
  } else {
    iterate(c, b, n);
  }
}


int main (int argc, char **argv) {
  double  a, b, ya, yb;
  double  xfrom, xto;
  int	  xsteps, xidx;
  char    ch;

  while (( ch = getopt(argc,argv,"v")) != -1 ) {	/* 実行時オプション */
    if ( ch == 'v' ) { verbose = 1; }			/* -v: 饒舌になる */
  }
  
  printf("x: from to steps> ");
  scanf( "%lf %lf %d", &xfrom, &xto, &xsteps );
  
  a = xfrom;
  if ((ya = func(a)) == 0) {
    printf( "Ans(%03d): %20.14lf %16.6le\n", 0, a, ya );
    puts("ya==0");
  }
  
  for( xidx=1; xidx <= xsteps; xidx++ ) {
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    yb = func(b);
    if (yb == 0) {
      printf( "Ans(%03d): %20.14lf %16.6le\n", 0, b, yb );
    } else if (ya * yb < 0) {
      iterate(a, b, 0);
    }
    a = b; ya = yb;
  }

  return 0;
}
