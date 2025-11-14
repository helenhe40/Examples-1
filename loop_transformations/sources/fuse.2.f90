! @@name:       fuse.2
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0

subroutine func(k, n, m, A, B)
  implicit none
  integer  :: k,n,m
  real     :: A(0:n-1),B(k:m+k-1)
  integer        :: i,j
  real, external :: f,g
  !$omp fuse
    do i = 0,n-1
      A(i) = f(i)
    end do
    do j = k,k+(m-1)
      B(j) = g(j)
    end do
  !$omp end fuse
end subroutine

subroutine func_equivalent(k, n, m, A, B)
  implicit none
  integer  :: k,n,m
  real     :: A(0:n-1),B(k:m+k-1)
  integer        :: ij
  real, external :: f,g

  do ij=0,max(n,m)-1
    if (ij < n) A(ij)   = f(ij)
    if (ij < m) B(ij+k) = g(ij+k)
  end do
end subroutine
