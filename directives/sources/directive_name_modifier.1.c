/*
* @@name:       directive_name_modifier.1
* @@type:       C   
* @@operation:  compile
* @@expect:     success
* @@version:    omp_6.0
*/
void conditional_parallel(int n, float a, float *x, float *y, int condition)
{
  // the if clause applies to all constituent directives that accept it
  // (all-constituents is the default property), in this case the parallel
  // directive
  #pragma omp parallel for if(condition)
  for (int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // the if clause applies to the parallel directive only
  #pragma omp parallel for if(parallel: condition)
  for (int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // the if clause applies to the parallel for constituent directive,
  // which has the effect of only applying to the parallel leaf directive
  #pragma omp parallel for if(parallel for: condition)
  for (int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }

  // the if clause applies to the taskloop simd constituent directive,
  // which has the effect of applying to both the taskloop and simd leaf
  // directives
  #pragma omp parallel masked taskloop simd if(taskloop simd: condition)
  for (int i=0; i<n; i++) {
    y[i] = a*x[i]+y[i];
  }
}
