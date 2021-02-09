add_executable(mmcat
    mmcat.c
)
target_link_libraries(mmcat PRIVATE
    tlpi_lib
)

add_executable(t_mmap
    t_mmap.c
)
target_link_libraries(t_mmap PRIVATE
    tlpi_lib
)