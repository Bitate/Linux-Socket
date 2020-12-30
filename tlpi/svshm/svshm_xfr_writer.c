#include "semun.h"
#include "svshm_xfr.h"

int main(int argc, char* argv[])
{
    int semid, shmid, bytes, xfrs;
    struct shmseg* shmp;
    union semun dummy;

    semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
}