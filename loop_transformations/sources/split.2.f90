! @@name:       split.2
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0
subroutine split_fuse(n, A)
  integer, intent(in)    :: n
  real,    intent(inout) :: A(n)

  !$omp fuse looprange(2,2)
  !$omp split counts(omp_fill,n,n)
  do i=0,2*n
    if(i >= 1) then 
      A(modulo((i-1),n)+1) = A(modulo((i-1),n)+1) + i
    endif
  enddo
end subroutine

subroutine split_fuse_equivalent1(n, A)
  integer, intent(in)    :: n
  real,    intent(inout) :: A(n)

 !$omp fuse looprange(2,2)
    do i=0,0
      if(i >= 1) then 
        A(modulo((i-1),n)+1) = A(modulo((i-1),n)+1) + i
      endif
    end do
  
    do i=1,n
      if(i >= 1) then 
        A(modulo((i-1),n)+1) = A(modulo((i-1),n)+1) + i
      endif
    enddo

    do i=n+1,2*n
      if(i >= 1) then 
        A(modulo((i-1),n)+1) = A(modulo((i-1),n)+1) + i
      endif
    enddo
 !$omp end fuse
end subroutine

subroutine split_fuse_equivalent2(n, A)
  integer, intent(in)    :: n
  real,    intent(inout) :: A(n)
     
  do i=0,0
    if(i >= 1) then 
      A(modulo((i-1),n)+1) = A(modulo((i-1),n)+1) + i
    endif
  end do

  do i = 1,n
    if(i >= 1) then 
      A(modulo((i-1  ),n)+1) = A(modulo((i-1  ),n)+1) + i
    endif
    if(i >= 1) then 
      A(modulo((i-1+n),n)+1) = A(modulo((i-1+n),n)+1) + i+n
    endif
  end do
end subroutine
