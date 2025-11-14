/*
* @@name:	apply_split.2
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
#include <math.h>
void do_something(int);

void func(int n, float* sines, float* cosines)
{
  #pragma omp fuse looprange(1,2) apply(split counts(n/2,omp_fill))
  {
    for (int i = 0; i < n; ++i)
      sines[i] = sin(2.0*M_PI*i/n);
    for (int j = 0; j < n; ++j)
      cosines[j] = cos(2.0*M_PI*j/n);
    for (int k = 0; k < n; ++k)
      do_something(k);
  }
}


void func_equivalent1(int n, float* sines, float* cosines)
{
    #pragma omp split counts(n/2,omp_fill)
    for (int ij = 0; ij < n; ++ij) {
      sines[ij]   = sin(2.0*M_PI*ij/n);
      cosines[ij] = cos(2.0*M_PI*ij/n);
    }
    for (int k = 0; k < n; ++k)
      do_something(k);
}

void func_equivalent2(int n, float* sines, float* cosines)
{
    for (int ij = 0; ij < n/2; ++ij) {
      sines[ij]   = sin(2.0*M_PI*ij/n);
      cosines[ij] = cos(2.0*M_PI*ij/n);
    }
    for (int ij = n/2; ij < n; ++ij) {
      sines[ij]   = sin(2.0*M_PI*ij/n);
      cosines[ij] = cos(2.0*M_PI*ij/n);
    }
    for (int k = 0; k < n; ++k)
      do_something(k);
}
