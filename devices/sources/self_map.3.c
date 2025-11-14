/*
* @@name:	self_map.3
* @@type:	C
* @@operation:	run
* @@expect:	rt-error
* @@version:	omp_6.0
*/

#include <omp.h>
#include <stdlib.h>

// Case 1: attempted self map when p[:n] is not accessible from device
// may result in a runtime error if the implementation is unable to make it
// accessible during the map.
void self_map_inaccessible_memory()
{
   const int n = 100;
   const int nbytes = n * sizeof(int);
   int *p = (int *)malloc(nbytes);

   const int dev = omp_get_default_device();
   const int accessible = omp_target_is_accessible(p, nbytes, dev);
   if (!accessible) {
      #pragma omp target_data map(self: p[:n]) // potential runtime error
      { 
         // ...
      }
   }
   free(p);
}

// Case 2: self map storage that is already mapped without a self map
// will result in a runtime error
void self_map_mapped_storage()
{
   const int n = 100;
   const int nbytes = n * sizeof(int);
   int *p = (int *)malloc(nbytes);

   const int dev = omp_get_default_device();
   #pragma omp target_data map(p[:n])
   { 
      const int not_self_mapped = omp_get_mapped_ptr(p, dev) != p;
      if (not_self_mapped) {
         // p[:n] is now mapped without a self map, but try to self map
         // it anyway
         #pragma omp target_data map(self:p[:n]) // runtime error
         {
            // ...
         }
      }
   }
   free(p);
}

// Case 3: self mapping a pointer that would get a different value due to
// pointer attachment will result in a runtime error.
void self_map_pointer_with_attachment()
{
   #define N 100
   int x[N];
   const int nbytes = N * sizeof(int);
   int *p = x;
   const int dev = omp_get_default_device();
   #pragma omp target_data map(x)
   { 
      const int not_self_mapped = omp_get_mapped_ptr(p, dev) != p;
      if (not_self_mapped) {
         // x is now mapped without a self map, but try (in vain) to self map
         // a pointer with pointer attachment to it.
         #pragma omp target_data map(self:p) map(p[:]) // runtime error
         {
            // ...
         }
      }
   }
}

int main()
{
   self_map_inaccessible_memory();
   self_map_mapped_storage();
   self_map_pointer_with_attachment();
   return 0;
}
