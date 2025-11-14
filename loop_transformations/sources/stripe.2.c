/*
* @@name:	stripe.2
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/
void func(float A[6][6])
{
  #pragma omp stripe sizes(2,2)
  for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 6; ++j)
      A[i][j] = i+j;
}

void func_equivalent(float A[6][6])
{
  for (int i1 = 0; i1 < 2; i1+=1)
    for (int j1 = 0; j1 < 2; j1+=1)
      for (int i2 = i1; i2 < 6; i2+=2)
        for (int j2 = j1; j2 < 6; j2+=2)
          A[i2][j2] = i2+j2;
}
