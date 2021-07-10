#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;

void handle_error(char* msg)
{
    cout << "error: " << msg << endl;
    exit(EXIT_FAILURE);
}

/**
 * @param[in] file_path
 *      File to be mapped into current process.
 * @param[in] offset
 *      The starting address of the file.
 * @param[in] length
 *      [offset, offset+length] is the area that will be sent to stdout.
 */
int main(int argc, char* argv[])
{
    if(argc < 3 || argc > 4)
        handle_error("argument count is not 3.");

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        handle_error("open file error");

    struct stat file_state;
    if(fstat(fd, &file_state) == -1)
        handle_error("get file state error");
    
    off_t offset = atoi(argv[2]);

    // offset for mmap() must be aligned
    off_t pa_offset = offset &~ (sysconf(_SC_PAGE_SIZE) - 1);

    if(offset >= file_state.st_size)
        handle_error("offset of not the end of the file");

    int length;
    if(argc == 4)
    {
        length = atoi(argv[3]);
        if(offset + length > file_state.st_size)
            length = file_state.st_size - offset;
    }
    else  // no length arg -> display to the end of file
    {
        length = file_state.st_size - offset;
    }

    char* addr = (char*)mmap(NULL, length+offset-pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);

    if(addr == MAP_FAILED)
        handle_error("map error");

    int s = write(STDOUT_FILENO, addr + offset - pa_offset, length);

    if(s!=length)
    {
        handle_error("write error");
    }

    munmap(addr, length + offset - pa_offset);
    close(fd);

    exit(EXIT_SUCCESS);
}