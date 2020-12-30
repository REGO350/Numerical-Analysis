#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PLUS	( + HUGE_VALL )
#define MINUS	( - HUGE_VALL )

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

  printf( "%20.1e %30.1le %35.1Le\n",    fabsf((nexttowardf(Real04,MINUS)-Real04)/Real04), fabs((nexttoward(Real08,MINUS)-Real08)/Real08), fabsl((nexttowardl(Real10,MINUS)-Real10)/Real10) );

  printf( "%20.12e %30.20le %35.25Le\n",   nexttowardf(Real04,MINUS), nexttoward(Real08,MINUS), nexttowardl(Real10,MINUS) );
  printf( "%20.12e %30.20le %35.25Le\n",               Real04,                   Real08,                    Real10        );
  printf( "%20.12e %30.20le %35.25Le\n",   nexttowardf(Real04,PLUS ), nexttoward(Real08,PLUS ), nexttowardl(Real10,PLUS ) );

  printf( "%20.1e %30.1le %35.1Le\n",    fabsf((nexttowardf(Real04,PLUS)-Real04)/Real04), fabs((nexttoward(Real08,PLUS)-Real08)/Real08), fabsl((nexttowardl(Real10,PLUS)-Real10)/Real10) );

  return 0;
}
