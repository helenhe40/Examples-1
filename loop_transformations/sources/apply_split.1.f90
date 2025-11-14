! @@name:       apply_split.1
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
function compute(i) result(computed)
  integer :: i
  real :: computed
  computed=real(i)
end function

subroutine split_composable(m, n, A)
   implicit none
   integer, intent(in ) :: m, n
   real,    intent(out) :: A(n)
   integer :: i
   real,external :: compute

   !$omp  split counts(m,omp_fill)  &
   !$omp& apply(split: target loop nowait map(from:A(1:m)), &
   !$omp&              parallel loop)
   do i=1,n
      A(i) = compute(i);
   end do

   !$omp taskwait

end subroutine

subroutine split_composable_equivalent(m, n, A)
   implicit none
   integer, intent(in ) :: m, n
   real,    intent(out) :: A(n)
   integer :: i
   real,external :: compute

  !$omp target loop nowait map(from:A(1:m))
  do i = 1,m
    A(i) = compute(i)
  end do

  !$omp parallel loop
  do i = m+1,n
    A(i) = compute(i)
  end do

  !$omp taskwait

end subroutine
