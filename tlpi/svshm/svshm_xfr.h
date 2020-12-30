#ifndef SVSHM_XFR_H
#define SVSHM_XFR_H

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "binary_sems.h"
#include "tlpi_hdr.h"

// Key for shared memory segment
#define SHM_KEY 0x1234

// Key for semaphore set
#define SEM_KEY 0x5678

// Permissions for our IPC objects
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

// Writer has access to shared memory
#define WRITE_SEM 0

// Reader has access to shared memory
#define READ_SEM 1

// Allow "cc -D" to override definition
#ifndef BUF_SIZE
#define BUF_SIZE 1024   // Size of transfer buffer
#endif

struct shmseg 
{
    int cnt;            // Number of bytes used in 'buf'
    char buf[BUF_SIZE]; // Data being transferred
};

#endif