/*
* @@name:       compound_names.1
* @@type:       C   
* @@operation:  compile
* @@expect:     success
* @@version:    omp_6.0
*/
void component_names(int n, float a, float *x, float *y)
{

  // equivalent to:
  //   #pragma omp parallel
  //   #pragma omp for
  #pragma omp parallel for 
  for(int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // equivalent to:
  //   #pragma omp parallel
  //   #pragma omp for simd
  #pragma omp parallel for simd
  for(int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // equivalent to:
  //   #pragma omp parallel
  //   #pragma omp masked
  //   #pragma omp taskloop
  #pragma omp parallel masked taskloop
  for(int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // equivalent to:
  //   #pragma omp target
  //   #pragma omp teams
  //   #pragma omp distribute parallel for
  #pragma omp target teams distribute parallel for
  for(int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }
}
