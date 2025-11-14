! @@name:	self_map.2
! @@type:	F-free
! @@operation:	run
! @@expect:	success
! @@version:	omp_6.0
module mod_data
   integer, parameter :: N = 100
   integer, private, target :: buf(N) = 0
   type Data
      integer, pointer :: p(:) => null()
      contains
         procedure :: init
   end type

   contains
   subroutine init(this)
      class(Data), intent(inout) :: this
      this%p => buf
   end subroutine
end module

program main
   use mod_data
   implicit none

   ! If the following directive is uncommented, all map operations in this
   ! compilation unit become self maps by default, and the explicit
   ! use of the self modifier below is unnecessary.
   ! !$omp requires self_maps

   ! Requiring unified_shared_memory would ensure that the data to be self-
   ! mapped is accessible from the device. Note that the unified_shared_memory
   ! requirement is implied by the self_maps requirement.
   !$omp requires unified_shared_memory

   type(Data) :: my_data
   integer :: i

   call my_data%init()

   ! The self maps of my_data in the following two target constructs allow
   ! for the p pointer to be used without pointer attachment on the
   ! device.
   !$omp target teams loop map(self: my_data)
   do i = 1, N
      my_data%p(i) = i
   end do
   !$omp target teams loop defaultmap(self: aggregate)
   do i = 1, N
      my_data%p(i) = 2 * my_data%p(i)
   end do

   do i = 1, N
      if (my_data%p(i) /= (2*i)) then
         error stop
      end if
   end do

end program
