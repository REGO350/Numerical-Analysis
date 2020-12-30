#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 中点公式 */


double fun( double x )
{
  return  1.0/x;
}

double FUN(double x)
{
  return log(x);
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main ( int argc, char **argv ){
  double  a, c, sum, SUM, diff, diff_percent;
  double  xfrom, xto, h;
  int	  xsteps, xidx;

  printf("x: from to steps> ");
  if ( argc >= 4 ) {
    xfrom  = atof( argv[1] );
    xto    = atof( argv[2] );
    xsteps = atol( argv[3] );
    printf( "%lf %lf %d\n", xfrom, xto, xsteps );
  } else {
    scanf( "%lf %lf %d", &xfrom, &xto, &xsteps );
  }
      
  sum = 0;
  h = (xto - xfrom) / xsteps;
  for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    c = a + h/2;
    sum += h*fun(c);
  }
  SUM = FUN(xto)-FUN(xfrom);
  diff = abst(sum-SUM);
  diff_percent = diff/SUM*100;
  printf( "ans:\t%20.15lf\n", sum );
  printf( "error:\t%20.15lf (%.10lf%%)\n", diff, diff_percent);
  return 0;
}
