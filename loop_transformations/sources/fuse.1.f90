! @@name:       fuse.1
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0

subroutine func(n, sines, cosines)
  implicit none
  integer,          intent(in)  :: n
  double precision, intent(out) :: sines(n), cosines(n)
  double precision, parameter   :: M_PI=4.0d0*DATAN(1.0d0)
  integer :: i, j

  !$omp fuse
    do i = 1, n
      sines(i) = sin(2.0d0*M_PI*(i-1)/n)
    end do
    do j = 1, n
      cosines(j) = cos(2.0d0*M_PI*(j-1)/n)
    end do
  !$omp end fuse
end subroutine

subroutine func_equivalent(n, sines, cosines)
  implicit none
  integer,          intent(in)  :: n
  double precision, intent(out) :: sines(n), cosines(n)
  double precision, parameter   :: M_PI=4.0d0*DATAN(1.0d0)
  integer :: ij
    do ij = 1, n
      sines(ij)   = sin(2.0d0*M_PI*(ij-1)/n)
      cosines(ij) = cos(2.0d0*M_PI*(ij-1)/n)
    end do
end subroutine
