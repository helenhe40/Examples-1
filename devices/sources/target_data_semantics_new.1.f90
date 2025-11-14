! @@name:      target_data_semantics_new.1
! @@type:       F-free
! @@operation:  compile
! @@expect:     success
! @@version:    omp_6.0

program main
  external do_stuff_with_a
  integer          :: t_
  double precision :: a

!! Case 1
!$omp target_data map(a)
  !$omp target map(a) nowait
    call do_stuff_with_a(a)
  !$omp end target
!$omp end target_data

!! Case 1E
!$omp target_enter_data map(a)   depend(out:  t_)                  !! T1
!$omp task transparent mergeable depend(inout:t_) default(shared)  !! T2
  !$omp taskgroup
    !$omp target map(a) nowait  !! T2_1
      call do_stuff_with_a(a)
    !$omp end target
  !$omp end taskgroup
!$omp end task
!$omp target_exit_data map(a)   depend(in: t_)       !! T3

!! Case 2
!$omp target_data map(a) nogroup
  !$omp target map(a) nowait
    call do_stuff_with_a(a)
  !$omp end target
!$omp end target_data

!! Case 2E
!$omp target_enter_data map(a) depend(out: t_)  !! T1
!$omp task transparent mergeable depend(inout: t_) default(shared)  !! T2
  !! no taskgroup
  !$omp target map(a) nowait  !! T2_1
    call do_stuff_with_a(a)
  !$omp end target
!$omp end task
!$omp target_exit_data map(a) depend(in: t_)      !! T3

!! Case 3
!$omp target_data map(a) depend(inout: a)
  !$omp target map(a) nowait depend(out: a)
    call do_stuff_with_a(a)
  !$omp end target
!$omp end target_data

!! Case 3E
!$omp target_enter_data map(a) depend(out: t_) depend(inout: a)  !! T1
!$omp task transparent mergeable depend(inout: t_) default(shared) &
!$omp&                           depend(inout: a) !! T2
  !$omp taskgroup
    !$omp target map(a) nowait depend(out: a)           !! T2_1
      call do_stuff_with_a(a)
    !$omp end target
  !$omp end taskgroup
!$omp end task
!$omp target_exit_data map(a) depend(in: t_) depend(inout: a)  !! T3

!! Case 4
!$omp target_data map(a) nogroup nowait depend(target_exit_data,in: a)
  !$omp target map(a) nowait depend(out: a)
    call do_stuff_with_a(a)
  !$omp end target
!$omp end target_data

!! Case 4E
!$omp target_enter_data map(a) nowait depend(out: t_)   !! T1
!$omp task transparent mergeable depend(inout: t_) default(shared) !! T2
  !$omp target map(a) nowait depend(out: a)           !! T2_1
    call do_stuff_with_a(a)
  !$omp end target
!$omp end task
!$omp target_exit_data map(a) nowait depend(in: t_) depend(in: a) !! T3

end program
