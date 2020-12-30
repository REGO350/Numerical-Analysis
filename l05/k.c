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
  double  a, b, c1, c2, sum, SUM, diff, diff_percent, best_diff=100, best_sum;
  double  xfrom=-1, xto=1, h;
  int	  xsteps, xidx, xstepsfrom, xstepsto, best_xsteps;

  printf("xsteps: from to> ");
  scanf( "%d %d", &xstepsfrom, &xstepsto);
  
  SUM = FUN(xto)-FUN(xfrom);
  for(xsteps=xstepsfrom;xsteps<=xstepsto;xsteps++){
    sum = 0;
    h = ( xto - xfrom ) / xsteps;
    for (xidx=0; xidx<xsteps; xidx++) {
      a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
      b = a + h;
      c1 = a + h/3;
      c2 = a+ 2*h/3;
      sum += (h/8)*(fun(a)+3*fun(c1)+3*fun(c2)+fun(b));
    }
    diff = abst(sum-SUM);
    if(diff<best_diff){
      best_diff = diff;
      best_sum = sum;
      best_xsteps = xsteps;
    }
  }
  diff_percent = best_diff/SUM*100000;
  printf( "comp ans(xsteps=%d):\t%10.20lf\n", best_xsteps, best_sum );
  printf( "real ans:\t%30.20lf\n", SUM );
  printf( "error:\t%38.20lf (%.15lfpcm)\n", best_diff, diff_percent);
  return 0;
}
