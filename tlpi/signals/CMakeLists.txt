add_executable(ouch_elf 
    ouch.c
)

add_executable(intquit_elf
    intquit.c
)

add_executable(kill_1_elf
    kill_1.c
)

add_executable(kill_2_elf
    kill_2.cpp
)

add_executable(t_sigqueue_elf
    t_sigqueue.c
)
target_link_libraries(t_sigqueue_elf PUBLIC
    tlpi_lib
)