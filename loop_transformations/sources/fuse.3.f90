! @@name:       fuse.3
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
subroutine func(n, A, B, C, D)
  implicit none
  integer,intent(in)  :: n
  real,   intent(out) :: A(n), B(n), C(n), D(n)
  integer        :: i, j, k, l 
  real, external :: e, f, g, h

  !$omp fuse looprange(2,2)
    do i = 1,n
      A(i) = e(i)
    end do
    do j = 1,n
      B(j) = f(j)
    end do
    do k = 1,n
      C(k) = g(k)
    end do
    do l = 1,n
      D(l) = h(l)
    end do
  !$omp end fuse
end subroutine

subroutine func_equivalent(n, A,  B,  C,  D)
  implicit none
  integer,intent(in)  :: n
  real,   intent(out) :: A(n), B(n), C(n), D(n)
  integer        :: i, jk, l 
  real, external :: e, f, g, h

  do i = 1,n
    A(i) = e(i)
  end do

  do jk = 1,n
    B(jk) = f(jk)
    C(jk) = g(jk)
  end do

  do l=1,n
    D(l) = h(l)
  end do
end subroutine
