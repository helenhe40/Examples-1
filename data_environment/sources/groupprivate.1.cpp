/*
* @@name:       groupprivate.1
* @@type:       C++ 
* @@operation:  run 
* @@expect:     success
* @@version:    omp_6.0
*/
#include <omp.h>
#include <stdio.h>

void init(int *x, int n, int tid)
{
   #pragma omp for
   for (int i = 0; i < n; i++)
     x[i] = tid + i;

}

void foo(int &sum, int tid)
{
   static int x[100];
   #pragma omp groupprivate(x) 
  
   init(x, 100, tid);
   
   #pragma omp for reduction(+:sum)
   for (int i = 0; i < 100; i++) {
     sum += x[i];
   }   
}
#pragma omp declare_target enter(foo)

int main()
{
   int sums[4] = {0,0,0,0};

   #pragma omp target teams num_teams(4) thread_limit(100)
   #pragma omp parallel
   foo(sums[omp_get_team_num()], omp_get_team_num());

   if( sums[0] != 4950 || sums[1] != 5050 ||
       sums[2] != 5150 || sums[3] != 5250 ){
     printf("FAILED\n");
     return 1;
   }   
   printf("PASSED\n");

   return 0;
}
