! @@name:       apply_split.2
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
subroutine func(n, sines, cosines)
  implicit none
  integer :: n
  double precision, intent(inout) :: sines(n), cosines(n)
  double precision, parameter     :: M_PI=4.0d0*DATAN(1.0d0)
  integer :: i,j,k
  external do_something

  !$omp fuse looprange(1,2) apply(split counts(n/2,omp_fill))
    do i = 1,n
      sines(i) = sin(2.0d0*M_PI*(i-1)/n)
    end do
    do j = 1,n
      cosines(j) = cos(2.0d0*M_PI*(j-1)/n)
    end do
    do k=1,n
      call do_something(k)
    end do
  !$omp end fuse

end subroutine

subroutine func_equivalent1(n, sines, cosines)
  implicit none
  integer :: n
  double precision, intent(inout) :: sines(n), cosines(n)
  double precision, parameter     :: M_PI=4.0d0*DATAN(1.0d0)
  integer :: ij,k
  external do_something

  !$omp split counts(n/2,omp_fill)
  do ij=1,n
    sines(ij)   = sin(2.0d0*M_PI*(ij-1)/n)
    cosines(ij) = cos(2.0d0*M_PI*(ij-1)/n)
  end do

  do k=1,n
    call do_something(k)
  end do

end subroutine

subroutine func_equivalent2(n, sines, cosines)
  implicit none
  integer :: n
  double precision, intent(inout) :: sines(n), cosines(n)
  double precision, parameter     :: M_PI=4.0d0*DATAN(1.0d0)
  integer :: ij,k
  external do_something

  do ij=1,n/2
    sines(ij)   = sin(2.0d0*M_PI*(ij-1)/n)
    cosines(ij) = cos(2.0d0*M_PI*(ij-1)/n)
  end do 

  do ij=(n/2)+1,n
    sines(ij)   = sin(2.0d0*M_PI*(ij-1)/n)
    cosines(ij) = cos(2.0d0*M_PI*(ij-1)/n)
  end do 

  do k=1,n
    call do_something(k)
  end do 

end subroutine
