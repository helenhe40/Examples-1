/*
* @@name:	affinity_control.1
* @@type:	C/C++
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
void work(); // may use additional free-agent threads

int main() 
{

   // input place partition controlled by OMP_PLACES
   // team size controlled by OMP_NUM_THREADS
   // affinity policy controlled by OMP_PROC_BIND
   // number of additional free-agent threads bounded by OMP_THREAD_LIMIT
   #pragma omp parallel
   work();

   return 0;
}
