! @@name:      target_teams_workdistribute.2
! @@type:      F-free
! @@operation: compile
! @@expect:    success
! @@version:   omp_6.0
module workdistribute_2
    implicit none
contains
    subroutine array_ops(aa, bb, cc, dd, ee, ff, n)
        implicit none

        integer :: n
        real, dimension(n, n) :: aa, bb, cc
        real, dimension(n, n) :: dd, ee, ff

        !$omp target teams workdistribute map(to:bb,dd,ee) &
        !$omp        map(tofrom:cc) map(from:aa,ff)
            aa = bb + cc
            cc = dd + ee
            ff = aa + cc
        !$omp end target teams workdistribute
    end subroutine array_ops
end module workdistribute_2
