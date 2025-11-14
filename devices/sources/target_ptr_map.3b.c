/*
* @@name:	target_ptr_map.3b
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/

#include <stdio.h>

int x[2], y[2];
int *p1;
#pragma omp declare_target enter(p1)
int *p2;

int foo()
{
  p1 = &x[0];
  p2 = &y[0];

  #pragma omp target_data map(p1[:2], y)
  { // device p1 becomes attached to device p1[:2]
    #pragma omp target // implicit map(x, y, p1, p2[:])
                       // p2 is predetermined firstprivate
    {
      // Accessing the mapped arrays x,y is OK here.
      x[0] = 1;
      y[0] = 2;

      p1[1] = 3; // ok, p1 attached to x
      p2[1] = 4; // ok prior to OpenMP 6.0: firstprivate p2
                 // points to y
    }
  }

  // prints x = 1, 3
  printf(" x = %d, %d\n", x[0], x[1]);
  // prints y = 2, 4
  printf(" y = %d, %d\n", y[0], y[1]);

  return 0;
}
