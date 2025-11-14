/*
* @@name: declare_target.8
* @@type: C
* @@operation: run
* @@expect: success
* @@version: omp_6.0
*/
#include <stdio.h>
#include <omp.h>

int sum;
int x[100];

/* Device-local sum and x */
#pragma omp declare_target local(sum, x)

#pragma omp begin declare_target
void init_x(int dev_id) 
{
  for (int j = 0; j < 100; ++j) {
    x[j] = j + dev_id;  
  }
}

void foo(void) 
{
  int i;
  #pragma omp for reduction(+:sum)
  for (i = 0; i < 100; i++) {
    sum += x[i];
  }
}
#pragma omp end declare_target

int main(void) 
{
  int ndev = omp_get_num_devices();
  if(!ndev){
    printf("No OpenMP target devices found.\n");
    return 1;
  }
  int host_sum[ndev];
  /* Initialize per device */
  for (int i = 0; i < ndev; i++) {
    #pragma omp target device(i)
    {
      init_x(i);   
      sum = 0;
    }
  }

  /* Parallel reductions on each device */
  for (int i = 0; i < ndev; i++) {
    #pragma omp target parallel map(from:host_sum[i]) device(i) nowait
    {
      foo();
      host_sum[i] = sum;
    }
  }
  #pragma omp taskwait

  for (int i = 0; i < ndev; i++) {
    printf("sum: %d, device: %d\n", host_sum[i], i);
  }
  return 0;
}