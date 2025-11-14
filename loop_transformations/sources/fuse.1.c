/*
* @@name:	fuse.1
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
#include <math.h>

void func(int n, double* sines, double* cosines)
{
  #pragma omp fuse
  {
    for (int i = 0; i < n; ++i)
      sines[i] = sin(2.0*M_PI*i/n);
    for (int j = 0; j < n; ++j)
      cosines[j] = cos(2.0*M_PI*j/n);
  }
}

void func_equivalent(int n, double* sines, double* cosines)
{
  for (int ij = 0; ij < n; ++ij) {
    sines[ij]   = sin(2.0*M_PI*ij/n);
    cosines[ij] = cos(2.0*M_PI*ij/n);
  }
}
