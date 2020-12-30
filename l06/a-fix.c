#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func( double t, double x ){
  return t + x; /*  dx/dt = func(t,x) */
}  

double func_ans(double t){
  return -t-1+exp(t);
}

int main (int argc, char **argv) {
  double  tfrom, tto, x0, tmp, xtmp, ans, error;
  int     k, i, n, tsteps, tmp2, j, l;

  printf("t0, x0, tto, number of tsteps(s)> ");
  if ( argc >= 5 ) {
    tfrom = atof( argv[1] );
    x0     = atof( argv[2] );
    tto   = atof( argv[3] );
    k = atof( argv[4] );
    printf( "%lf %lf %lf %d\n", tfrom, x0, tto, k );
  } else {
    scanf( "%lf %lf %lf %d", &tfrom, &x0, &tto, &k);
  }	/* delta_t には２の累乗分の１を使う */
  
  double delta_t[k];
  printf("tsteps (accending order)> ");
  for(i=0;i<k;i++){ 
    scanf("%d", &tsteps);
    if(i==0) tmp2 = tsteps;
    delta_t[i] = (tto-tfrom)/tsteps;
  }
  tsteps++;
  double delta_x[k][tsteps], t[k][tsteps], x[k][tsteps];

  for(i=0;i<k;i++){
    for(j=0;j<tsteps;j++){
      delta_x[i][j] = 0;
      t[i][j] = 0;
      x[i][j] = 0;
    }
  }

  for(i=0;i<k;i++){ 
    t[i][0] = tfrom;
    x[i][0] = x0;
  }

  for(i=0;i<k;i++){
    n=0; j=0, xtmp=x0;
    while ( t[i][j] <= tto ) {
      delta_x[i][j] = func(t[i][j],x[i][j])*delta_t[i]; 
      j++; n++;
      t[i][j] = tfrom+delta_t[i]*n; 
      xtmp += delta_x[i][j-1]; 
      x[i][j] = xtmp;
    }
  }

  tmp2++;
  for(l=0;l<tmp2;l++){
    ans = func_ans(t[0][l]);
    error = (ans-x[0][l])/ans*100;
    puts("####################################################");
    printf("t=%.14lf:\n", t[0][l]);
    printf("real ans: %.14lf\n", ans);
    printf("x:%.14lf    delta_x:%.14lf    error:%.14lf%%\n", x[0][l], delta_x[0][l], error);
    for(i=1;i<k;i++){
      for(j=0;j<tsteps;j++){
        if(t[i][j]==t[0][l]){
          ans = func_ans(t[0][l]);
          error = (ans-x[i][j])/ans*100;
          printf("x:%.14lf    delta_x:%.14lf    error:%.14lf%%\n", x[i][j], delta_x[i][j], error);
          break;
        }
      }
    }
  }

  return 0;
}
