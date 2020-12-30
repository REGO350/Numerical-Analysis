#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* シンプソン 3/8 公式 */

double fun( double x )
{
  return x*exp(x);
}

double FUN(double x)
{
  return exp(x)*(x-1);
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main ( int argc, char **argv ){
  double  a, b, c1, c2, sum, SUM, diff, diff_percent;
  double  xfrom, xto, h;
  int	  xsteps, xidx;

  printf("x: from to steps> ");
  if ( argc >= 3 ) {
    xfrom  = atof( argv[1] );
    xto    = atof( argv[2] );
    xsteps = atol( argv[3] );
    printf( "%lf %lf %d\n", xfrom, xto, xsteps );
  } else {
    scanf( "%lf %lf %d", &xfrom, &xto, &xsteps );
  }

  sum = 0;
  h = ( xto - xfrom ) / xsteps;
  for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    b = a + h;
    c1 = a + h/3;
    c2 = a+ 2*h/3;
    sum += (h/8)*(fun(a)+3*fun(c1)+3*fun(c2)+fun(b));
  }
  SUM = FUN(xto)-FUN(xfrom);
  diff = abst(sum-SUM);
  diff_percent = diff/SUM*100000;
  printf( "comp ans:\t%10.15lf\n", sum );
  printf( "real ans:\t%10.15lf\n", SUM );
  printf( "error:\t%25.15lf (%.15lfpcm)\n", diff, diff_percent);
  return 0;
}
