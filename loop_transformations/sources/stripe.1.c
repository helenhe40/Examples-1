/*
* @@name:	stripe.1
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
void func(int A[12][6])
{
  #pragma omp stripe sizes(4)
  for (int i = 0; i < 12; ++i)
    for (int j = 0; j < 5; ++j)
      A[i][j+1] = A[i][j]/32;
}

void func_equivalent(int A[12][6])
{
  for (int i1 = 0; i1 < 4; i1+=1)
    for (int i2 = i1; i2 < 12; i2+=4)
      for (int j = 0; j < 5; ++j)
        A[i2][j+1] = A[i2][j]/32;
}
