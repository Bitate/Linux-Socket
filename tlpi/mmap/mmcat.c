/**
 * Demonstrate the use of mmap() to create a private file mapping.
 * This is a simplified cat(1), which maps the entire file named 
 * in its command-line argument, and then writes the contents of 
 * the mapping to standard output.
 */
#include "../lib/tlpi_hdr.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    /**
     * Obtain the size of the file and use it to specify the size of
     * the mapping and the size of the buffer to be written 
     */
    struct stat file_status_buffer;
    if (fstat(fd, &file_status_buffer) == -1)
        errExit("fstat");
    
    /**
     * variable addr represents the starting address of new mapping.
     * 
     * We specify the offset to 0 and length as the size of the file denoted by __fd
     * to map the entire file.
     */
    char* addr = mmap(NULL, file_status_buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (write(STDOUT_FILENO, addr, file_status_buffer.st_size) != file_status_buffer.st_size)
        fatal("partial/failed write");

    exit(EXIT_SUCCESS);
}
