/*
* @@name:	target_ptr_map.1
* @@type:	C
* @@operation:	run
* @@expect:	success
* @@version:	omp_5.0
*/
#include <stdio.h>
#include <stdlib.h>
#define N 100

int main()
{
  int *ptr1 = 0;
  int *ptr2 = 0;
  int *ptr3 = 0;
  int arr[N];

  ptr1 = (int *)malloc(sizeof(int)*N);
  ptr2 = (int *)malloc(sizeof(int)*N);

  #pragma omp target map(ptr1, ptr1[:N]) map(ptr2[:N] )
  {
     for (int i=0; i<N; i++)
     {
         ptr1[i] = i;
         ptr2[i] = i;
         arr[i] = i;
     }

     // ptr1 must not change since it is an attached pointer
     // *(++ptr1) = 9;

     // ok to modify firstprivate ptr2; this assigns to ptr2[1]
     *(++ptr2) = 9;

     // ok to modify firstprivate ptr3
     ptr3 = (int *)malloc(sizeof(int)*N);

     for (int i=0; i<N; i++) ptr3[i] = 5;

     for (int i=0; i<N; i++) ptr1[i] += ptr3[i];

     free(ptr3);
  }

  // prints 6 and 9 for ptr1[1] and ptr2[1]
  printf(" %d %d\n",ptr1[1], ptr2[1]);

  free(ptr1);
  free(ptr2);
  return 0;
}
