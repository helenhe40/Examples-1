! @@name:	stripe.1
! @@type:	F-free
! @@operation:	compile
! @@expect:	success
! @@version:	omp_6.0
subroutine func(A)
  implicit none
  integer :: A(6,12)
  integer :: i, j

  !$omp stripe sizes(4)
  do i = 1, 12
    do j = 1, 5
      A(j+1,i) = A(j,i)/32
    end do
  end do
end subroutine

subroutine func_equivalent(A)
  implicit none
  integer :: A(6,12)
  integer :: i1, i2, j

  do i1 = 1, 4
    do i2 = i1, 12, 4
      do j = 1, 5
        A(j+1,i2) = A(j,i2)/32
      end do
    end do
  end do
end subroutine
