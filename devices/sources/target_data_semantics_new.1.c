/*
* @@name:	target_data_semantics_new.1
* @@type:	C
* @@operation:	compile
* @@expect:	success
* @@version:	omp_6.0
*/

extern void do_stuff_with_a(double);
extern int t_;

#define N 1000
int main()  {
  double a;

// Case 1 
#pragma omp target_data map(a)
{
  #pragma omp target map(a) nowait
    do_stuff_with_a(a);
}

// Case 1E 
#pragma omp target_enter_data map(a) depend(out: t_)    // T1
#pragma omp task transparent mergeable depend(inout: t_) default(shared)  //T2
#pragma omp taskgroup
{
  #pragma omp target map(a) nowait  // T2_1
    do_stuff_with_a(a);
}
  #pragma omp target_exit_data map(a) depend(in: t_)       // T3

// Case 2 
#pragma omp target_data map(a) nogroup
{ 
  #pragma omp target map(a) nowait
    do_stuff_with_a(a);
}

// Case 2E 
#pragma omp target_enter_data map(a) depend(out: t_)      //  T1
#pragma omp task transparent mergeable depend(inout: t_) default(shared)  // T2
{   // no taskgroup
  #pragma omp target map(a) nowait  // T2_1
    do_stuff_with_a(a);
}
#pragma omp target_exit_data map(a) depend(in: t_)     // T3

// Case 3
#pragma omp target_data map(a) depend(inout: a)
{
  #pragma omp target map(a) nowait depend(out: a)
    do_stuff_with_a(a);
}

// Case 3E 
#pragma omp target_enter_data map(a) depend(out: t_) depend(inout: a) //  T1
#pragma omp task transparent mergeable depend(inout: t_)  \
                                   default(shared) depend(inout: a) // T2
#pragma omp taskgroup
{
  #pragma omp target map(a) nowait depend(out: a)    //  T2_1
    do_stuff_with_a(a);
}
#pragma omp target_exit_data map(a) depend(in: t_) depend(inout: a) // T3

// Case 4
#pragma omp target_data map(a) nogroup nowait depend(target_exit_data,in: a)
{
  #pragma omp target map(a) nowait depend(out: a)
    do_stuff_with_a(a);
}

// Case 4E 
#pragma omp target_enter_data map(a) nowait depend(out: t_)   // T1
#pragma omp task transparent mergeable depend(inout: t_) default(shared) // T2
{
  #pragma omp target map(a) nowait depend(out: a)    // T2_1
    do_stuff_with_a(a);
}
#pragma omp target_exit_data map(a) nowait depend(in: t_) depend(in: a) // T3

return 0;

} 
