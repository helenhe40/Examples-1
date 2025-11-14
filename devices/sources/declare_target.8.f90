! @@name: declare_target.8
! @@type: F-free
! @@operation: run 
! @@expect: success
! @@version: omp_6.0
module dev_mod
  implicit none
  integer :: sum
  integer :: x(100)

  !$omp declare_target local(sum, x)

contains

  subroutine init_x(dev_id)
    integer, value :: dev_id   
    integer :: j
    !$omp declare_target
    do j = 1, 100
      x(j) = (j-1) + dev_id    
    end do
  end subroutine init_x
 
  subroutine foo()
    integer :: i
    !$omp declare_target

    !$omp do reduction(+:sum)
    do i = 1, 100
      sum = sum + x(i)
    end do
  end subroutine foo

end module dev_mod

program main
  use omp_lib
  use dev_mod
  implicit none

  integer :: ndev, i
  integer, allocatable :: host_sum(:)

 
  ndev = omp_get_num_devices()
  if (ndev <= 0) then
    print *, 'No OpenMP target devices found.'
    stop
  end if
  allocate(host_sum(0:ndev-1))

  do i = 0, ndev-1
    !$omp target device(i) 
      call init_x(i)
      sum = 0
    !$omp end target
  end do

  do i = 0, ndev-1
    !$omp target parallel map(from: host_sum(i)) device(i) nowait
      call foo()
      host_sum(i) = sum
    !$omp end target parallel
  end do
 !$omp taskwait
 
  do i = 0, ndev-1
    print *, 'sum: ', host_sum(i), ', device: ', i
  end do

  deallocate(host_sum)

end program main
