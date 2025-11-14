#include <math.h>

#define DO_PRAGMA(x) _Pragma(#x)
#define OMP_PRAGMA(...) DO_PRAGMA(omp __VA_ARGS__)

#ifdef MATCH_CLAUSE
OMP_PRAGMA(begin declare_variant MATCH_CLAUSE)
#endif
static void exp_pi_diff(double *d, double my_pi, const int N)
{
  #pragma omp metadirective                             \
      when( construct={teams}: loop bind(teams) )       \
      when( construct={parallel}: loop bind(parallel) ) \
      otherwise( loop bind(thread) )
  for(int i = 0; i < N; i++)
    d[i] = exp( (M_PI-my_pi)*i );
}
#ifdef MATCH_CLAUSE
OMP_PRAGMA(end declare_variant)
#endif
