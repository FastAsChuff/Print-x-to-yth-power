#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <gmp.h> //sudo apt-get install libgmp3-dev

// gcc bigpower.c -o bigpower.bin -lm -lgmp -O3 -march=native -Wall

uint64_t atou64(char *in) {
  uint64_t res = 0;
  while (*in) {
    res *= 10;
    res += *in - '0';
    in++;
  }
  return res;
}

int main(int argc, char** argv) {
  _Bool validargs = true;
  uint64_t x;
  uint64_t y;
  if (argc < 3) {
    validargs = false;
  } else {   
    x = atou64(argv[1]);
    y = atou64(argv[2]);
    if ((x == 0) || (y == 0)) validargs = false;
    if (argc > 3) {
      uint64_t maxdigits = atou64(argv[3]);
      if (maxdigits < (double)y*log10(x)) {
        printf("Too many digits!\n");
        exit(1);
      }
    }
  } 
  if (!validargs) {
    printf("Prints decimal representation of x^y for positive integers x,y.\n0 < x, y < 2^64\nUsage:- %s x y [maxdigits]\n", argv[0]);
    exit(1);
  }  
  mpz_t mpzn;
  mpz_init(mpzn);
  mpz_set_ui(mpzn, x);
  mpz_ui_pow_ui(mpzn,x,y);
  printf("%lu^%lu = ",x,y);
  gmp_printf("%Zd\n", mpzn);
  mpz_clear(mpzn);
}
