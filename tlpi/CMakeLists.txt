set(this tlpi)

project(${this} C)

add_subdirectory(lib)
add_subdirectory(svipc)
add_subdirectory(svshm)
add_subdirectory(svmsg)
add_subdirectory(altio)
add_subdirectory(signals)
add_subdirectory(memalloc)
add_subdirectory(mmap)