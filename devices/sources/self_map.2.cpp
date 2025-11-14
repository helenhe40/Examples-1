//
// @@name:	self_map.2
// @@type:	C++
// @@operation:	run
// @@expect:	success
// @@version:	omp_6.0

#include <omp.h>
#include <stdlib.h>

// If the following directive is uncommented, all map operations in this
// compilation unit become self maps by default, and the explicit use
// of the self modifier below is unnecessary.
// #pragma omp requires self_maps

// Requiring unified_shared_memory would ensure that the data to be self-
// mapped is accessible from the device. Note that the unified_shared_memory
// requirement is implied by the self_maps requirement.
#pragma omp requires unified_shared_memory

int main()
{
   #define N 100

   class Data {
   private:
      int buf[N];
   public:
      int* p;
      Data() : buf {} { p = buf; }
   };

   Data my_data;

   // The self maps of my_data in the following two target constructs allow
   // for the p pointer to be used without pointer attachment on the device.
   #pragma omp target teams loop map(self: my_data)
   for (int i = 0; i != N; ++i)
      my_data.p[i] = i;
   #pragma omp target teams loop defaultmap(self: aggregate)
   for (int i = 0; i != N; ++i)
      my_data.p[i] *= 2;

   for (int i = 0; i != N; ++i)
      if (my_data.p[i] != (2*i))
         return 1;

   return 0;
}
