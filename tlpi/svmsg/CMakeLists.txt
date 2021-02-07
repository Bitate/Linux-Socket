add_executable(svmsg_create
    svmsg_create.c
)
target_link_libraries(svmsg_create
    tlpi_lib
)

add_executable(svmsg_send
    svmsg_send
)
target_link_libraries(svmsg_send
    tlpi_lib
)

add_executable(svmsg_receive
    svmsg_receive
)
target_link_libraries(svmsg_receive
    tlpi_lib
)