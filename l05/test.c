#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ( int argc, char **argv ){
  char func[8][15]={"mid_point", "trapezoidal", "simpson", "simpson_3_8", "gauss_2", "gauss_3", "chebyshev_2", "chebyshev_3"};
  printf("%s", func[1]);
  return 0;
}
