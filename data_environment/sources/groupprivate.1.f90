! @@name:       groupprivate.1
! @@type:       F-free
! @@operation:  run
! @@expect:     success
! @@version:    omp_6.0
module mfunc
contains
  subroutine init(x, n, tid)
    implicit none
    integer, intent(in)  :: tid, n
    integer, intent(out) :: x(n)
    integer              :: i
    
    ! Initialize the array with the thread number
    !$omp do
    do i = 1, n
      x(i) = tid + i
    end do
  end subroutine init

  subroutine foo(sum, tid)
    implicit none
    integer, intent(inout) :: sum
    integer, intent(in)    :: tid
    integer                :: i
    integer, save          :: x(100)
    !$omp groupprivate(x)
    !$omp declare_target 

    call init(x,100,tid)

    ! Perform the reduction operation
    !$omp do reduction(+:sum) 
    do i = 1, 100
      sum = sum + x(i)
    end do
  end subroutine foo

end module mfunc

program main
  use mfunc
  use omp_lib
  implicit none

  integer :: sums(4) = (/ 0, 0, 0, 0 /)
  integer :: team_num, thread_num

  !$omp target teams num_teams(4) thread_limit(100)
  !$omp parallel private(team_num, thread_num)
    team_num = omp_get_team_num()
    thread_num = omp_get_thread_num()
    call foo(sums(team_num+1), team_num)
  !$omp end parallel
  !$omp end target teams

  if( sums(1) /= 5050 .or. sums(2) /= 5150 .or. &
      sums(3) /= 5250 .or. sums(4) /= 5350 ) then
    print*, "FAILED"
    stop 1
  endif
  print *, "PASSED"
end program
