! @@name:	taskloop.1
! @@type:	F-free
! @@operation:	compile
! @@expect:	success
! @@version:	omp_4.5
subroutine parallel_work
   integer i
   integer j
!$omp taskgroup

!$omp task
   call long_running_task()   ! can execute concurrently
!$omp end task

!$omp taskloop private(j) grainsize(500) nogroup
   do i=1,10000               ! can execute concurrently
      do j=1,i
         call loop_body(i, j)
      end do
   end do
!$omp end taskloop

!$omp end taskgroup
end subroutine
