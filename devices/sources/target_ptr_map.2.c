/*
* @@name:	target_ptr_map.2
* @@type:	C
* @@operation:	run
* @@expect:	success
* @@version:	omp_5.1
*/
#include <stdio.h>
#include <stdlib.h>
#define N 100

#pragma omp begin declare target
  int *p;
  void use_arg_p(int *p, int n);
  void use_global_p(int n);
#pragma omp end declare target

int main()
{
  int i;
  p = (int *)malloc(sizeof(int)*N);

  // device p becomes attached to corresponding p[:N] on device
  #pragma omp target map(p[:N])
  {
    for (i=0; i<N; i++) p[i] = i;
    use_arg_p(p, N);
    use_global_p(N);
  } // value of host p is preserved

  // prints 3 and 297 for p[1] and p[N-1]
  printf(" %d %d\n", p[1], p[N-1]);

  free(p);
  return 0;
}

void use_arg_p(int *q, int n)
{
  int i;
  for (i=0; i<n; i++)
    q[i] *= 2;
}

void use_global_p(int n)
{
  int i;
  for (i=0; i<n; i++) {
    // this will access the array section to which
    // device p was attached on entry to the target region
    p[i] += i;
  }
}
