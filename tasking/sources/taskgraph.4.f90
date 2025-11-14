! @@name:	taskgraph.4
! @@type:	F-free
! @@operation:	run
! @@expect:	success
! @@version:	omp_6.0

program taskgraph_4
   integer, parameter :: N = 100
   integer, parameter :: M = 8
   integer :: sums(M) = (/ (0, i=1,M) /)
   integer :: i, j

   do i = 1, M
      !$omp parallel masked
         call exec_taskgraph(i)
      !$omp end parallel masked
   end do

   do i = 1, M
      if (sums(i) /= check_sum(n)) then
         print *, "check failed"
         stop 1
      end if
   end do
   print *, "check passed"

   contains

   subroutine exec_taskgraph(i)
      integer, intent(in) :: i
      !$omp taskgraph
      block
         integer, save :: x(N), y(N), z(N)
         ! Task A
         !$omp task depend(out: x)
            call get_vals(x, N)
         !$omp end task
         ! Task B
         !$omp task depend(out: y)
            call get_vals(y, N)
         !$omp end task
         ! Task C
         !$omp task depend(in: x,y)
            call do_compute(z, x, y, N)
            !$omp simd reduction(+:sums(i))
            do j = 1, N
               sums(i) = sums(i) + z(j)
            end do
         !$omp end task
      end block
   end subroutine

   subroutine get_vals(b, n)
      integer, intent(out) :: b(*)
      integer, intent(in) :: n
      integer :: j
      do j = 1, n
         b(j) = j
      end do
   end subroutine

   subroutine do_compute(z, x, y, n)
      integer, intent(out) :: z(*)
      integer, intent(in) :: x(*), y(*), n
      integer :: j
      do j = 1, n
         z(j) = x(j) * y(j) - x(j)
      end do
   end subroutine

   function check_sum(n) result(cs)
      integer, intent(in) :: n
      integer :: cs
      cs = ( n * (n+1) * (2*n-2) ) / 6
   end function
end program

