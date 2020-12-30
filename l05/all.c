#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fun( double x ){
  return x*exp(x);
}

double FUN(double x){
  return exp(x)*(x-1);
}

double abst(double t){
  if(t<0){
    return -t;
  }else{
    return t;
  }
}

double scale( double c, double a, double b ){
  return (a*(1.0-c)+b*(1.0+c))/2.0;
}

double mid_point(double xfrom, double xto, int xsteps){
  double a,c,h,sum=0;
  int xidx;
  h = (xto - xfrom) / xsteps;
  for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    c = a + h/2;
    sum += h*fun(c);
  }
  return sum;
}

double trapezoidal(double xfrom, double xto, int xsteps){
   double  a, b, h, sum=0;
   int xidx;
   h = (xto - xfrom) / xsteps;
   for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps; 
    b = a + h;
    sum += (h/2)*(fun(a)+fun(b));
  }
  return sum;
}

double simpson(double xfrom, double xto, int xsteps){
  double  a, b, c, sum=0, h;
  int xidx;
  h = ( xto - xfrom ) / xsteps;
  for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;	
    b = a + h;
    c = a + h/2;
    sum += (h/6)*(fun(a)+4*fun(c)+fun(b));
  }
  return sum;
}

double simpson_3_8(double xfrom, double xto, int xsteps){
  double  a, b, c1, c2, sum=0, h;
  int xidx;
  h = ( xto - xfrom ) / xsteps;
  for (xidx=0; xidx<xsteps; xidx++) {
    a = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    b = a + h;
    c1 = a + h/3;
    c2 = a+ 2*h/3;
    sum += (h/8)*(fun(a)+3*fun(c1)+3*fun(c2)+fun(b));
  }
  return sum;
}

double gauss_2(double xfrom, double xto, int xsteps){
  double  x1, x2, sum=0, a, b, h;
  int xidx;
  h = (xto-xfrom)/xsteps;
  a = xfrom;
  for( xidx=1; xidx<=xsteps; xidx++ ) {
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    x1 = scale(-sqrt(1.0/3.0), a, b);
    x2 = scale(sqrt(1.0/3.0), a, b);
    sum += (h/2)*(fun(x1)+fun(x2));
    a = b;
  }
  return sum;
}

double gauss_3(double xfrom, double xto, int xsteps){
  double  x1, x2, x3, sum=0, a, b, h;
  int xidx;
  h = (xto-xfrom)/xsteps;
  a = xfrom;
  for( xidx=1; xidx<=xsteps; xidx++ ) {
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    x1 = scale(-sqrt(3.0/5.0), a, b);
    x2 = scale(0, a, b);
    x3 = scale(sqrt(3.0/5.0), a, b);
    sum += (h/2)*((5*fun(x1)/9)+(8*fun(x2)/9)+(5*fun(x3)/9));
    a = b;
  }
  return sum;
}

double chebyshev_2(double xfrom, double xto, int xsteps){
  double  x1, x2, sum=0, a, b, h;
  int xidx;
  h = (xto-xfrom)/xsteps;
  a = xfrom;
  for( xidx=1; xidx<=xsteps; xidx++ ) {
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    x1 = scale(-sqrt(1.0/3.0), a, b);
    x2 = scale(sqrt(1.0/3.0), a, b);   
    sum += (h/2)*(1.0*fun(x1)+1.0*fun(x2));
    a = b;
  }
  return sum;
}

double chebyshev_3(double xfrom, double xto, int xsteps){
  double  x1, x2, x3, sum=0, a, b, h;
  int xidx;
  h = (xto-xfrom)/xsteps;
  a = xfrom;
  for( xidx=1; xidx<=xsteps; xidx++ ) {
    b = (xfrom * (xsteps - xidx) + xto * xidx) / xsteps;
    x1 = scale(-1.0/sqrt(2.0), a, b);
    x2 = scale(0.0, a, b);
    x3 = scale(1.0/sqrt(2.0), a, b);
    sum += (h/2)*(2*fun(x1)/3+2*fun(x2)/3+2*fun(x3)/3);
    a = b;
  }
  return sum;
}

double (*func_ptr[8])(double xfrom, double xto, int xsteps) = {mid_point, trapezoidal, simpson, simpson_3_8, gauss_2, gauss_3, chebyshev_2, chebyshev_3};

int main ( int argc, char **argv ){
  double  xfrom, xto;
  int	  xsteps, xstepsfrom, xstepsto, i;

  double sum[8], diff[8], best_diff[8], best_sum[8], diff_percent[8];
  int  best_xsteps[8];
  char func[8][15]={"mid_point", "trapezoidal", "simpson", "simpson_3_8", "gauss_2", "gauss_3", "chebyshev_2", "chebyshev_3"};

  printf("x: from to> ");
  scanf( "%lf %lf", &xfrom, &xto);
  printf("xsteps: from to> ");
  scanf( "%d %d", &xstepsfrom, &xstepsto);
  printf("###################################################\n");
  double  SUM=FUN(xto)-FUN(xfrom); //real sum
  for(i=0;i<8;i++){best_diff[i]=100;}
  for(xsteps=xstepsfrom;xsteps<=xstepsto;xsteps++){
    for(i=0;i<8;i++){
      sum[i] = (*func_ptr[i])(xfrom, xto, xsteps);
      diff[i] = abst(sum[i]-SUM);
      if(diff[i]<best_diff[i]){
        best_diff[i] = diff[i];
        best_sum[i] = sum[i];
        best_xsteps[i] = xsteps;
        diff_percent[i] = best_diff[i]/SUM*100000;
      }
    }
  }

  printf( "real ans:\t%30.20lf\n", SUM );
  for(i=0;i<8;i++){
    printf("###################################################\n");
    printf("calculation method: %s\n", func[i]);
    printf("comp ans(xsteps=%d):\t%10.20lf\n", best_xsteps[i], best_sum[i]);
    printf( "error:\t%38.20lf (%.15lfpcm)\n", best_diff[i], diff_percent[i]);
  }
  printf("###################################################\n");
  double best_diff_percent=diff_percent[0];
  int best_acc=0, smallest_xsteps=best_xsteps[0], smallest_xsteps_method=0;
  for(i=0;i<8;i++){
    if(diff_percent[i]<best_diff_percent){
      best_diff_percent=diff_percent[i];
      best_acc=i;
    }
    if(best_xsteps[i]<smallest_xsteps){
      smallest_xsteps=best_xsteps[i];
      smallest_xsteps_method=i;
    }
  }
  printf("Best accuracy is:    %.15lfpcm (%s)\n", best_diff_percent, func[best_acc]);
  printf("Smallest xsteps is:  %d (%s)\n", smallest_xsteps, func[smallest_xsteps_method]);
  return 0;
}