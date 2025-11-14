/*
* @@name:	target_ptr_map.4
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_5.2
*/
#include <stdlib.h>
#include <omp.h>

void do_work(int *ptr, const int size);

int main() 
{
   const int n = 1000;
   const int buf_size = sizeof(int) * n;
   const int dev = omp_get_default_device();

   // malloc'd memory may or may not be accessible on a non-host
   // device
   int *ptr = (int *) malloc(buf_size);

   const int accessible = omp_target_is_accessible(ptr, buf_size, dev);

   // Make ptr firstprivate if the memory it points to is already accessible. 
   // Otherwise, map the memory.
   #pragma omp metadirective \
      when(user={condition(accessible)}: target firstprivate(ptr)) \
      otherwise(target map(ptr[:n]))
   {
      do_work(ptr, n);
   } 

   free(ptr);
   return 0;
}
