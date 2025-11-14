! @@name:       split.1
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
subroutine adder(m, n, A, B, C)
    implicit none
    integer, intent(in)    :: m,n
    real,    intent(inout) :: A(0:n-1)
    real,    intent(in)    :: B(0:n-1),C(0:n-1)
    integer                :: i

    !$omp split counts(m,1,omp_fill)
    do i = 0,n-1
      A(i) = A(m) + B(i) + C(i)
    end do
end subroutine

subroutine adder_equivalent(m, n, A, B, C)
    implicit none
    integer, intent(in)    :: m,n
    real,    intent(inout) :: A(0:n-1)
    real,    intent(in)    :: B(0:n-1),C(0:n-1)
    integer                :: i

    do i = 0,m-1
      A(i) = A(m) + B(i) + C(i)
    end do

    do i = m,m
      A(i) = A(m) + B(i) + C(i)
    end do

    do i = m+1,n-1
      A(i) = A(m) + B(i) + C(i)
    end do

end subroutine
