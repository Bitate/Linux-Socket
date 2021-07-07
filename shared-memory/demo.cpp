#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int N = 5;

    int* ptr = (int*)mmap(NULL, N*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if(ptr == MAP_FAILED)
    {
        cout << "mmap failed" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Original integers" << endl;
    for(int i = 0; i < N; ++i)
    {
        ptr[i] = i+1;
        cout << ptr[i] << " " << endl;
    }

    switch(fork())
    {
        case -1:
        {
            cout << "fork error" << endl;
            exit(EXIT_FAILURE);
        }

        case 0:
        {   
            cout << "child mutiplies each int by 100" << endl;

            for(int i = 0; i < N; ++i)
            {
                ptr[i] = ptr[i] * 100;
            } 
            break;
        }

        default:
        {
            wait(NULL);
            cout << "Parent check integers: " << endl;
            for(int i = 0; i < N; ++i)
            {
                cout << ptr[i] << " " << endl;
            }
            int err = munmap(ptr, N*sizeof(int));

            if(err != 0)
            {
                cout << "unmap error" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
}
