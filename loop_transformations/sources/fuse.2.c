/*
* @@name:	fuse.2
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
float f(int);
float g(int);

void func(int k, int n, int m, float* A, float* B)
{
  #pragma omp fuse
  {
    for (int i = 0; i < n; ++i)
      A[i] = f(i);
    for (int j = k; j < k+m; ++j)
      B[j] = g(j);
  }
}

void func_equivalent(int k, int n, int m, float* A, float* B)
{
  for (int ij = 0; ij < (m>n ? m : n); ++ij) {
    if (ij < n) A[ij] = f(ij);
    if (ij < m) B[k+ij] = g(k+ij);
  }
}
