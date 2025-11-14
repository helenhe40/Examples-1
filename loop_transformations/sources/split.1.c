/*
* @@name:       split.1
* @@type:       C   
* @@operation:  run
* @@expect:     success
* @@version:    omp_6.0
*/
void adder(int m, int n, float* A, float* B, float* C){

  // Split out vectorizable portion of loop.
  #pragma omp split counts(m,1,omp_fill)
  for(int i = 0; i<n; i++){
    A[i] = A[m] + B[i] + C[i];
  }
}

void adder_equivalent(int m, int n, float* A, float* B, float* C){

  for(int i = 0; i<m; i++){
    A[i] = A[m] + B[i] + C[i];
  }

  for(int i = m; i<m+1; i++){
    A[i] = A[m] + B[i] + C[i];
  }

  for(int i = m+1; i<n; i++){
    A[i] = A[m] + B[i] + C[i];
  }

}
