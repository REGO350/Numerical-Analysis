#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 台形公式 */


double fun( double x )
{
  return  ((x+2)*x+3)*x+4;
}

double FUN(double x)
{
  return pow(x,4)/4+2*pow(x,3)/3+3*pow(x,2)/2+4*x;
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main ( int argc, char **argv ){
  double  a, b, sum, SUM, diff, diff_percent;
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
    b = a + h;
    sum += (h/2)*(fun(a)+fun(b));
  }
  SUM = FUN(xto)-FUN(xfrom);
  diff = abst(sum-SUM);
  diff_percent = diff/SUM*100;
  printf( "ans:\t%20.15lf\n", sum );
  printf( "error:\t%20.15lf (%.10lf%%)\n", diff, diff_percent);
  return 0;
}
