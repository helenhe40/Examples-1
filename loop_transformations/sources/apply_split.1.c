/*
* @@name:       apply_split.1
* @@type:       C
* @@operation:  compile
* @@expect:     success
* @@version:    omp_6.0
*/
float compute(int i){return (float)i; }

void split_composable(int m, int n, float A[n])
{
   #pragma omp split counts(m,omp_fill) \
       apply(split: target loop nowait map(from:A[0:m]), \
                    parallel loop)
   for (int i = 0; i < n; ++i)
      A[i] = compute(i);

   #pragma omp taskwait
}

void split_composable_equivalent(int m, int n, float A[n])
{
    #pragma omp target loop nowait map(from:A[0:m])
    for (int i = 0; i < m; ++i)
       A[i] = compute(i);

    #pragma omp parallel loop
    for (int i = m; i < n; ++i)
       A[i] = compute(i);

   #pragma omp taskwait
}
