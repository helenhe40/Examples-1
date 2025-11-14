! @@name:      target_teams_workdistribute.1
! @@type:      F-free
! @@operation: run
! @@expect:    success
! @@version:   omp_6.0
module axpy_mod
    implicit none
contains
    subroutine axpy_workdistribute(a, x, y, n)
        implicit none

        integer :: n
        real :: a
        real, dimension(n) :: x, y

        !$omp target teams workdistribute map(to:x) map(tofrom:y)
            y = a * x + y
        !$omp end target teams workdistribute
    end subroutine axpy_workdistribute
end module axpy_mod

program ftn_axpy
    use axpy_mod, only: axpy_workdistribute
    implicit none

    integer, parameter :: N = 1024 * 1024
    real :: a, x0, y0
    real, dimension(N) :: x, y

    a = 2.0
    x = 2.0  ! initialize arrays
    y = 1.0
    x0 = 2.0 ! initialize scalars for validation
    y0 = 1.0

    write (*, '(A)') 'calling axpy'
    call axpy_workdistribute(a, x, y, N)
    write (*,'(A,F4.2,A,F4.2)') 'sum ', sum(y) / N, ' expected ', a * x0 + y0
end program ftn_axpy
