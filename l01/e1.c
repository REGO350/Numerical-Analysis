#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


int main (int argc, char **argv) {
  char		str[256];
  float		Real04;
  double	Real08;
  long double	Real10;

  if ( argc >=2 ) {
    Real10 = strtold( argv[1], NULL );
  } else {
    printf( "> " );
    Real10 = strtold( fgets( str, 256, stdin ), NULL );
  }

  Real04 = Real10;
  Real08 = Real10;

  printf( "04: %10.8f %20.18f %30.28f\n",      Real04, Real04, Real04 );
  printf( "08: %10.8lf %20.18lf %30.28lf\n",   Real08, Real08, Real08 );
  printf( "10: %10.8Lf %20.18Lf %30.28Lf\n",   Real10, Real10, Real10 );


  return 0;
}
