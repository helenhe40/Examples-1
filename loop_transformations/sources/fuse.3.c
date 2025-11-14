/*
* @@name:	fuse.3
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
float e(int);
float f(int);
float g(int);
float h(int);

void func(int n, float* A, float* B, float* C, float* D)
{
  #pragma omp fuse looprange(2,2)
  {
    for (int i = 0; i < n; ++i)
      A[i] = e(i);
    for (int j = 0; j < n; ++j)
      B[j] = f(j);
    for (int k = 0; k < n; ++k)
      C[k] = g(k);
    for (int l = 0; l < n; ++l)
      D[l] = h(l);
  }
}

void func_equivalent(int n, float* A, float* B, float* C, float* D)
{
  for (int i  = 0;  i < n; ++i)
    A[i] = e(i);
  for (int jk = 0; jk < n; ++jk) {
    B[jk] = f(jk);
    C[jk] = g(jk);
  }
  for (int l  = 0;  l < n; ++l)
    D[l] = h(l);
}
