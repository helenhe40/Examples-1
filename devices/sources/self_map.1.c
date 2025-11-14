/*
* @@name:	self_map.1
* @@type:	C
* @@operation:	run
* @@expect:	success
* @@version:	omp_6.0
*/

#include <omp.h>

// If the following directive is uncommented, all map operations in this
// compilation unit become self maps by default, and the explicit use of
// the self modifier below is unnecessary.
// #pragma omp requires self_maps

// Requiring unified_shared_memory would ensure that the data to be self-mapped
// is accessible from the device. Note that the unified_shared_memory
// requirement is implied by the self_maps requirement.
#pragma omp requires unified_shared_memory

#define N 100

int main()
{
   typedef struct {
      int *start, *end;
      int buf[N];
   } Data;

   Data my_data;
   my_data.start = my_data.buf;
   my_data.end = my_data.buf + N;

   // the self map of my_data in the following two target constructs allows for
   // the start and end pointers to be used without pointer attachments on the
   // device
   int i = 0;
   #pragma omp target parallel for linear(i) map(self: my_data)
   for (int *p = my_data.start; p != my_data.end; ++p) {
      *p = i++;
   }
   #pragma omp target teams loop defaultmap(self:aggregate)
   for (int *p = my_data.start; p != my_data.end; ++p) {
      *p = *p * 2;
   }

   i = 0;
   for (int *p = my_data.start; p != my_data.end; ++p) {
      if (*p != (2*i)) {
         return 1;
      }
      i++;
   }

   return 0;
}

