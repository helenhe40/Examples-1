/*
* @@name:       invalid_compound_names.1
* @@type:       C   
* @@operation:  compile
* @@expect:     ct-error
* @@version:    omp_6.0
*/
void f();
void g(float);

void invalid_compound_names(int n, float *x)
{

  // invalid: repeated parallel disallowed
  #pragma omp parallel target parallel
  f();

  // invalid: target cannot be nested inside teams
  #pragma omp teams target
  f();

  // invalid: sections may only be appended to parallel
  #pragma omp teams sections
  f();

  // invalid: masked may only be appended to parallel
  #pragma omp teams masked
  f();

  // invalid: multiple data-mapping constituents
  #pragma omp target_data parallel target map(x[:n])
  f();

  // invalid: task and taskloop both generate tasks in
  // same parallel region
  #pragma omp task taskloop
  for (int i = 0; i < n; i++) {
    g(x[i]);
  }
}
