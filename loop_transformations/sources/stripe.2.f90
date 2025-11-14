! @@name:	stripe.2
! @@type:	F-free
! @@operation:	compile
! @@expect:	success
! @@version:	omp_6.0
subroutine func(A)
  implicit none
  real :: A(6,6)
  integer :: i, j

  !$omp stripe sizes(2,2)
  do i = 1, 6
    do j = 1, 6
      A(j,i) = i+j
    end do
  end do
end subroutine

subroutine func_equivalent(A)
  implicit none
  real :: A(6,6)
  integer :: i1, i2, j1, j2

  do i1 = 1, 2
    do j1 = 1, 2
      do i2 = i1, 6, 2
        do j2 = j1, 6, 2
          A(j2,i2) = i2+j2
        end do
      end do
    end do
  end do
end subroutine
