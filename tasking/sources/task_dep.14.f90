! @@name:	task_dep.14
! @@type:	F-free
! @@operation:	run
! @@expect:	success
! @@version:	omp_6.0
program main
  implicit none
  integer :: x, y

  !$omp parallel masked
    !$omp task depend(out: x)
      x = 0          ! T1
    !$omp end task

    !$omp task depend(out: y) transparent
      y = 100        ! T2 - transparent task
      !$omp task depend(inout: x)
        x = x + 1    ! T3 - must wait on T1
      !$omp end task
    !$omp end task

    !$omp task depend(in: x, y)
      print *, "x = ", x, ", y = ", y   ! T4 - must wait on T2, T3
      !!        x = 1, y = 100
    !$omp end task
  !$omp end parallel masked

end program
