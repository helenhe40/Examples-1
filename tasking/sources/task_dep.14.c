/*
* @@name:	task_dep.14
* @@type:	C
* @@operation:	run
* @@expect:	success
* @@version:	omp_6.0
*/
#include <stdio.h>

int main()
{
  int x, y;

  #pragma omp parallel masked
  {
    #pragma omp task depend(out: x)
      x = 0;        // T1

    #pragma omp task depend(out: y) transparent
    {               // T2 - transparent task
      y = 100;
      #pragma omp task depend(inout: x)
        x++;        // T3 - must wait on T1
    }

    #pragma omp task depend(in: x, y)
      printf("x = %d, y = %d\n", x, y);    // T4 - must wait on T2, T3
      //      x = 1, y = 100
  }

  return 0;
}
