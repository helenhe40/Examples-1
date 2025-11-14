/*
* @@name:	target_ptr_map.3a
* @@type:	C
* @@operation:	compile
* @@expect:	unspecified
* @@version:	omp_6.0
*/

int x[2], y[2];
int *p1;
#pragma omp declare_target enter(p1)
int *p2;

int foo()
{
  p1 = &x[0];
  p2 = &y[0];

  #pragma omp target  // implicit map(x, y, p1, p2[:])
                      // p2 is predetermined firstprivate
  { // no pointer attachment for p1 to x on entry

    // Accessing the mapped arrays x,y is OK here.
    x[0] = 1;
    y[0] = 2;

    p1[1] = 3;  // undefined behavior
    p2[1] = 4;  // undefined behavior prior to 6.0, but
                // ok in 6.0: firstprivate p2 points to y
  }

  return 0;
}
