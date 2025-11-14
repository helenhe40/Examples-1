! @@name:       compound_names.1
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
subroutine component_names(n, a, x, y)
  implicit none
  integer, intent(in)    :: n
  real,    intent(in)    :: a, x(n)
  real,    intent(inout) :: y(n)
  integer                :: i

!! equivalent to:
!!   !$omp parallel
!!   !$omp do
!!     ...
!!   !$omp end parallel
  !$omp parallel do 
  do i = 1,n 
    y(i) = a*x(i)+y(i)
  end do

!! equivalent to:
!!   !$omp parallel
!!   !$omp do simd
!!     ...
!!   !$omp end parallel
  !$omp parallel do simd
  do i = 1,n 
    y(i) = a*x(i)+y(i)
  end do


!! equivalent to:
!!   !$omp parallel
!!   !$omp masked
!!   !$omp taskloop
!!     ...
!!   !$omp end masked
!!   !$omp end parallel
  !$omp parallel masked taskloop
  do i = 1,n 
    y(i) = a*x(i)+y(i)
  end do

!! equivalent to:
!!   !$omp target
!!   !$omp teams
!!   !$omp distribute parallel do
!!     ...
!!   !$omp end teams
!!   !$omp end target
  !$omp target teams distribute parallel do
  do i = 1,n 
    y(i) = a*x(i)+y(i)
  end do

end subroutine
