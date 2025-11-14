! @@name:	cas.1
! @@type:	F-free
! @@operation:	run
! @@expect:	success
! @@version:	omp_6.0
module mm
  integer, parameter :: N = 10

contains
  subroutine init(val)
    implicit none
    integer :: val(N), i

    val = [ (i-1, i=1, N) ]
    val(N/2  ) =  2*N
    val(N/2+1) = -2*N
  end subroutine
end module

program main
  use mm
  implicit none
  integer :: val_min = 2*N, val_max = -2*N
  integer :: val(N), i

  call init(val)

  !$omp parallel do num_threads(2)
  do i = 2, N-1

    ! compare and update val_min using one atomic form
    !$omp atomic compare
    if (val(i) < val_min) val_min = val(i)

    ! compare and update val_max using another atomic form
    !$omp atomic compare
    val_max = (val(i) > val_max ? val(i) : val_max)
  end do

  if (val_max /= 2*N .or. val_min /= -2*N) then
    print *, "FAILED"
    error stop
  else
    print *, "PASSED"
  endif
end
