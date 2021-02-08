add_executable(mmcat
    mmcat.c
)
target_link_libraries(mmcat PRIVATE
    tlpi_lib
)