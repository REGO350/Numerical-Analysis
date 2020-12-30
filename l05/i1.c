#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* シンプソン公式 */


double fun( double x )
{
  return (((x+2)*x+3)*x+4)*x+5;
}

double FUN(double x)
{
  return pow(x,5)/5+pow(x,4)/2+pow(x,3)+2*pow(x,2)+5*x;
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

int main ( int argc, char **argv ){
  double  a, b, c, sum, SUM, diff, diff_percent;
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

  double min=100000.0;
  long i=0;
  while(i<10000000){
    sum = 0;
    h = ( xto - xfrom ) / xsteps;
    for (xidx=0; xidx<xsteps; xidx++) {
      a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;	
      b = a + h;
      c = a + h/2;
      sum += (h/6)*(fun(a)+4*fun(c)+fun(b));
    }
    SUM = FUN(xto)-FUN(xfrom);
    diff = abst(sum-SUM);
    if(diff<=min){
      min = diff;
    }else{
      break;
    }
    xsteps++;
    i++;
  }
  diff_percent = diff/SUM*100;
  printf( "ans:\t%20.15lf\n", sum );
  printf( "error:\t%20.15lf (%.15lf%%)\n", diff, diff_percent);
  printf("xsteps: \t%20d\n", xsteps-1 );
  return 0;
}
