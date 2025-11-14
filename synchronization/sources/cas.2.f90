! @@name:	cas.2
! @@type:	F-free
! @@operation:	run
! @@expect:	success
! @@version:	omp_6.0
module mq
  integer, parameter :: N = 10

  type tNode
    integer :: id
    type(tNode), pointer :: next
  end type
  type tQueue
    type(tNode), pointer :: head, tail
  end type

contains
  subroutine enqueue(queue, node)
    implicit none
    type(tQueue) :: queue
    type(tNode), target :: node
    logical result

    result = .false.

    !$omp atomic read
    node%next => queue%tail

    do while (.not.result)
      !$omp atomic compare capture
      result = associated(queue%tail, node%next)
      if (result) then
        queue%tail => node
      else
        node%next => queue%tail
      end if
      !$omp end atomic
    end do
  end subroutine
end module

program main
  use mq
  implicit none
  type(tQueue) :: q
  type(tNode), target :: nodes(N)
  type(tNode), pointer :: node
  integer :: id_check(N)
  integer :: i, id

  ! Initializing
  do i = 1, N
    nodes(i)%next => null()
    nodes(i)%id = i
    id_check(i) = -1
  end do

  q%tail => nodes(1)   ! Fill initial tail

  ! Enqueue
  !$omp parallel do num_threads(2)
  do i = 2, N
    call enqueue(q, nodes(i))
  end do

  ! Checking Results Below
  node => q%tail
  do while (associated(node%next))
    id_check(node%id) = node%id   ! Store found id at position id 
    node => node%next
  end do
  id_check(node%id) = node%id     ! checking also the 1st node here

  do id = 1, N                    ! all ids should be found
    if (id /= id_check(id)) then
      print *, "FAILED"
      error stop
    endif
  end do
  print *, "PASSED"
end
