! @@name:	affinity_control.1
! @@type:	F-free
! @@operation:	compile
! @@expect:	success
! @@version:	omp_6.0
program main
   interface
      subroutine work ! may use additional free-agent threads
      end subroutine work
   end interface

   ! input place partition controlled by OMP_PLACES
   ! team size controlled by OMP_NUM_THREADS
   ! affinity policy controlled by OMP_PROC_BIND
   ! number of additional free-agent threads bounded by OMP_THREAD_LIMIT
   !$omp parallel
      call work()
   !$omp end parallel
end program
