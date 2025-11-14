/*
* @@name:       split.2
* @@type:       C   
* @@operation:  compile
* @@expect:     success
* @@version:    omp_6.0
*/
void split_fuse(int n, float A[n])
{
   #pragma omp fuse looprange(2,2)
   #pragma omp split counts(omp_fill,n,n)
   for (int i = 0; i < 1+2*n; ++i)
      if (i >= 1)
         A[(i-1)%n] += i;
}

void split_fuse_equivalent1(int n, float A[n])
{
   #pragma omp fuse looprange(2,2)
   {   
      for (int i = 0; i < 1; ++i)
        if(i >= 1) A[(i-1)%n] += i;
      for (int i = 1; i < 1+n; ++i)
        if(i >= 1) A[(i-1)%n] += i;
      for (int i = 1+n; i < 1+2*n; ++i)
        if(i >= 1) A[(i-1)%n] += i;
   }   
}

void split_fuse_equivalent2(int n, float A[n])
{
      for (int i = 0; i < 1; ++i)
         if(i >= 1) A[(i-1)%n] += i;
      for (int i = 1; i < 1+n; ++i) {
         if(i >= 1) A[(i-1  )%n] += i;
         if(i >= 1) A[(i-1+n)%n] += i+n;
      }   
}
